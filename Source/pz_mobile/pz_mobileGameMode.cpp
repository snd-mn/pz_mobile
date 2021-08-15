// Copyright Epic Games, Inc. All Rights Reserved.

#include "pz_mobileGameMode.h"
#include "pz_mobilePlayerController.h"
#include "pz_mobileCharacter.h"
#include "UObject/ConstructorHelpers.h"

Apz_mobileGameMode::Apz_mobileGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = Apz_mobilePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}