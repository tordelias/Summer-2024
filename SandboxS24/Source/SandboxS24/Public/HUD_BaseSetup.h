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
	
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	

	// All on screen widgets to add to the HUD on BeginPlay
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UUserWidget>> AllUIWidgets;

public:
	// Current list of created UI widgets that are constantly active on screen
	TArray<class UUserWidget*> CreatedWidgets;

	// Game (HUD) 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	UUserWidget* UI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	UUserWidget* CrossHair;


	// Game Menus (Inventory, Pause, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	UUserWidget* InventoryWidget;


	// Menu (Main, Options, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	UUserWidget* MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	UUserWidget* OptionsMenu;


	//Modals (Dialogs, Popups, etc.)

public:
	int CurrentID;
	void CollapseAllWidgets();
	void WantsToOpenWidget(int WidgetID);
	void ExpandWidget(int WidgetID);

};
