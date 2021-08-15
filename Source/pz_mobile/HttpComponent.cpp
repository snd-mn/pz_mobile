// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpComponent.h"

#include <string>

#include "Interfaces/IHttpResponse.h"


// Sets default values for this component's properties
UHttpComponent::UHttpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Http = &FHttpModule::Get();
	// ...
}


// Called when the game starts
void UHttpComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UHttpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
static const wchar_t* blub = TEXT("{	\"gps\":{\"lat\":\"51.50889155160364\",	\"lon\":\"7.464675695954779\"}}");;
static FString* blbbb = new FString(blub);


/*Http call*/
void UHttpComponent::MyHttpCall()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	
	Request->SetURL(TEXT("http://127.0.0.1:12224/tiles"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"), TEXT("Basic dXNlckBsb2NhbC10cmluaXR5Lm9yZzpzdXBlcnNhZmVwYXNzd29yZA=="));
	
	FString payload (TEXT("{\"gps\":{\"lat\":\"51.50889155160364\",\"lon\":\"7.464675695954779\"}}\0"));
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *payload)
	Request->SetContentAsString(*payload);

	Request->OnProcessRequestComplete().BindUObject(this, &UHttpComponent::OnResponseReceived);

	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void UHttpComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString())
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, Response->GetContentAsString());
}
