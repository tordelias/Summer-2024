// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_BaseSetup.h"
#include "Blueprint/UserWidget.h"

void AHUD_BaseSetup::BeginPlay()
{
	Super::BeginPlay();

	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());

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


	// If any widgets need to be added
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

	CollapseAllWidgets();

	//CreatedWidgets[2]->SetVisibility(ESlateVisibility::Visible);

	/*UE_LOG(LogTemp, Warning, TEXT("CreatedWidgets: %d"), CreatedWidgets.Num());
	UE_LOG(LogTemp, Warning, TEXT("AllUIWidgets: %d"), AllUIWidgets.Num());*/

}

//Collapse all widgets 
void AHUD_BaseSetup::CollapseAllWidgets()
{
	for (UUserWidget* widget : CreatedWidgets)
	{
		widget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AHUD_BaseSetup::ExpandWidget(int WidgetID)
{
	if(CurrentWidget == CreatedWidgets[WidgetID]) // Not sure this works TODO: Test thiss
	{
		
	}
	else
	{
		CollapseAllWidgets();
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHUD_BaseSetup::DrawHUD()
{
	Super::DrawHUD();
}


//void AHUD_BaseSetup::Tick(float DeltaTime)
//{
//
//	Super::Tick(DeltaTime);
//
//}

