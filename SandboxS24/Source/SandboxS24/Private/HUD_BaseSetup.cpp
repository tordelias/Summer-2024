// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_BaseSetup.h"
#include "Blueprint/UserWidget.h"

void AHUD_BaseSetup::BeginPlay()
{
	Super::BeginPlay();

	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());

	CurrentID = 100; // Set to a number that is not in the array


	//Add all widgets to the HUD
	if(UI)
	{
		AllUIWidgets.Add(UI->GetClass());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No UI Widget set in HUD_BaseSetup"));
	}

	if(CrossHair)
	{
		AllUIWidgets.Add(CrossHair->GetClass());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No CrossHair Widget set in HUD_BaseSetup"));
	}

	if (InventoryWidget)
	{
		AllUIWidgets.Add(InventoryWidget->GetClass());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Inventory Widget set in HUD_BaseSetup"));
	}

	if(MainMenu)
	{
		AllUIWidgets.Add(MainMenu->GetClass());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No MainMenu Widget set in HUD_BaseSetup"));
	}

	if (OptionsMenu)
	{
		AllUIWidgets.Add(OptionsMenu->GetClass());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No OptionsMenu Widget set in HUD_BaseSetup"));
	}


	// Adds all defined widgets to the viewport
	if (AllUIWidgets.Num() > 0)
	{
		// Iterate through all widgets
		for (TSubclassOf<UUserWidget> widget : AllUIWidgets)
		{
			// Creates an instance of the widget and add to viewport
			UUserWidget* createdWidget = CreateWidget<UUserWidget>(GetWorld(), widget);
			createdWidget->AddToViewport();

			// Store instanced widget in array
			CreatedWidgets.Add(createdWidget);
		}
	}

	CollapseAllWidgets(); //Collapse all widgets

	WantsToOpenWidget(0); //Open the first widget (UI)

}

//Collapse all widgets 
void AHUD_BaseSetup::CollapseAllWidgets()
{
	for (UUserWidget* widget : CreatedWidgets)
	{
		widget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

// Checks if the widget is already open and if not sends the widget ID to ExpandWidget
void AHUD_BaseSetup::WantsToOpenWidget(int WidgetID)
{
	if (CurrentID == WidgetID)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentID == WidgetID"));
		return;
	}
	else
	{
		ExpandWidget(WidgetID);
	}
}

// Expands the widget with the given ID
void AHUD_BaseSetup::ExpandWidget(int WidgetID)
{
	CurrentID = WidgetID;
	//what is CurrentID?
	UE_LOG(LogTemp, Warning, TEXT("CurrentID: %f"), CurrentID);

	CollapseAllWidgets();
	CreatedWidgets[CurrentID]->SetVisibility(ESlateVisibility::Visible);
	
}

void AHUD_BaseSetup::DrawHUD()
{
	Super::DrawHUD();
}


