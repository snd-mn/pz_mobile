// Copyright Epic Games, Inc. All Rights Reserved.

#include "pz_mobilePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "pz_mobileCharacter.h"
#include "Engine/World.h"

Apz_mobilePlayerController::Apz_mobilePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	HttpComponent = CreateDefaultSubobject<UHttpComponent>("HttpComponent");
	NodeRegistry = CreateDefaultSubobject<UNodeRegistry>("NodeRegistry");
}

void Apz_mobilePlayerController::Interact_Implementation(UNodePz* Node)
{
	const FString interactUrl = "http://127.0.0.1:12224/interact";
	UVaRestJsonObject* RestObject = NewObject<UVaRestJsonObject>();
	const FString Payload = FString::Printf(TEXT("{\"targetSystem\":\"1\",\"node\":\"%lld\"}"), Node->id);
	RestObject->DecodeJson(Payload);

	FVaRestCallDelegate& Callback = *new FVaRestCallDelegate();
	Callback.BindUFunction(this, FName("InteractHandleResponse"));
	RestObject->DecodeJson(Payload);

	TMap<FString,FString> headers = TMap<FString,FString>();
	headers.Add(TEXT("Authorization"),TEXT("Basic dXNlckBsb2NhbC10cmluaXR5Lm9yZzpzdXBlcnNhZmVwYXNzd29yZA=="));
	headers.Add(TEXT("Content-Type"),TEXT("application/json"));
	
	VaRestSubsystem->CallExtended(interactUrl, EVaRestRequestVerb::POST, EVaRestRequestContentType::json, RestObject, Callback, headers);
}

void Apz_mobilePlayerController::InteractHandleResponse_Implementation(UVaRestRequestJSON* Request)
{
	bool ret = true;
	
	UE_LOG(LogTemp, Warning, TEXT("InteractHandleResponse_Implementation: %i"), Request->GetResponseCode())
	ret &= Request->GetResponseCode() == 200;
	ret &= Request->GetResponseObject()->GetStringField("info").Equals("fine!");

	if(ret)
	{
		if(IsValid(GetPawn()))
		{
			Apz_mobileCharacter* character = Cast<Apz_mobileCharacter>(GetPawn());
			character->Jump();
		}
	}
}

bool Apz_mobilePlayerController::InitVaRestSubsystem_Implementation()
{
	if (GEngine != nullptr)
	{
		VaRestSubsystem = GEngine->GetEngineSubsystem<UVaRestExtendedSubsystem>();
		if (VaRestSubsystem != nullptr)
		{
			return true;
		}
	}
	return false;
}

void Apz_mobilePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void Apz_mobilePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &Apz_mobilePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &Apz_mobilePlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &Apz_mobilePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &Apz_mobilePlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &Apz_mobilePlayerController::OnResetVR);
}

void Apz_mobilePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void Apz_mobilePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (Apz_mobileCharacter* MyPawn = Cast<Apz_mobileCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void Apz_mobilePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void Apz_mobilePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void Apz_mobilePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void Apz_mobilePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void Apz_mobilePlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitVaRestSubsystem();
}
