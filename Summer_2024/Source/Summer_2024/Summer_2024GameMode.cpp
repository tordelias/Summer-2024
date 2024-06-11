// Copyright Epic Games, Inc. All Rights Reserved.

#include "Summer_2024GameMode.h"
#include "Summer_2024PlayerController.h"
#include "Summer_2024Character.h"
#include "UObject/ConstructorHelpers.h"

ASummer_2024GameMode::ASummer_2024GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASummer_2024PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}