// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "HUD_BaseSetup.h"
#include "Engine/LocalPlayer.h"


void AMPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//get the enhanced input subsystem

}

void AMPlayerController::SetupInputComponent()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	//{

	//	EnhancedInputComponent->BindAction(IA_Inventory, ETriggerEvent::Triggered, this, &AMPlayerController::OpenInventory);

	//}
}

//void AMPlayerController::OpenInventory()
//{
//	UE_LOG(LogTemp, Warning, TEXT("IA works"));
//	AHUD_BaseSetup* HUD = Cast<AHUD_BaseSetup>(this->GetClass()); 
//	HUD->ExpandWidget(2); 
//
//}