// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_BaseSetup.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXS24_API AHUD_BaseSetup : public AHUD
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	// Game (HUD) 

	// Game Menus (Inventory, Pause, etc.)

	//UPROPERTY(EditAnywhere, Category = "Game Menu")
	//class UUserWidget* CurrentWidget;

	// Menu (Main, Options, etc.)

	//Modals (Dialogs, Popups, etc.)


};
