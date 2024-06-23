// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_BaseSetup.h"
#include "Blueprint/UserWidget.h"
#include"UserInterface/Interaction/InteractionWidget.h"
#include"UserInterface/MainMenu.h"
#include "Interfaces/InteractionInterface.h"



AHUD_BaseSetup::AHUD_BaseSetup()
{

}

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

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetclass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetclass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

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
	UE_LOG(LogTemp, Warning, TEXT("I AM RUNNING"));
	if (CurrentID == WidgetID)
	{
		if(CurrentID == 2)
		{
			APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
			if (PC)
			{
				PC->bShowMouseCursor = false;
				PC->bEnableClickEvents = false;
				PC->bEnableMouseOverEvents = false;
				PC->SetInputMode(FInputModeGameOnly());
			}
			CollapseAllWidgets();
			ExpandWidget(0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CurrentID == WidgetID"));
		}
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
	APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	switch(CurrentID)
	{
		case 0:
			UE_LOG(LogTemp, Warning, TEXT("UI"));
			CollapseAllWidgets();
			CreatedWidgets[CurrentID]->SetVisibility(ESlateVisibility::Visible);
			break;
		case 1:
			UE_LOG(LogTemp, Warning, TEXT("CrossHair"));
			CreatedWidgets[CurrentID]->SetVisibility(ESlateVisibility::Visible);
			break;
		case 2:
			UE_LOG(LogTemp, Warning, TEXT("Inventory"));
			CollapseAllWidgets();
			CreatedWidgets[CurrentID]->SetVisibility(ESlateVisibility::Visible);
			if(PC)
			{
				PC->bShowMouseCursor = true;
				PC->bEnableClickEvents = true;
				PC->bEnableMouseOverEvents = true;
				PC->SetInputMode(FInputModeGameAndUI());
			}
			break;
		case 3:
			UE_LOG(LogTemp, Warning, TEXT("MainMenu"));
			CollapseAllWidgets();
			CreatedWidgets[CurrentID]->SetVisibility(ESlateVisibility::Visible);
			break;
		case 4:
			UE_LOG(LogTemp, Warning, TEXT("OptionsMenu"));
			CollapseAllWidgets();
			CreatedWidgets[CurrentID]->SetVisibility(ESlateVisibility::Visible);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Invalid WidgetID"));
			break;
	}

	CollapseAllWidgets();
	CreatedWidgets[CurrentID]->SetVisibility(ESlateVisibility::Visible);
	
}



void AHUD_BaseSetup::DrawHUD()
{
	Super::DrawHUD();
}



void AHUD_BaseSetup::DisplayMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHUD_BaseSetup::HideMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AHUD_BaseSetup::ShowInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHUD_BaseSetup::HideInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AHUD_BaseSetup::UpdateInteractionWidget(const FInteractableData* InteractableData)
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}


