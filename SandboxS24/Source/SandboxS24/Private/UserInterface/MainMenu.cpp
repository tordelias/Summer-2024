// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"

void UMainMenu::NativeOnInitialized()
{
	//Super::NativeOnInitialized;
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct(); 

	PlayerCharacter = Cast<AMCharacter>(GetOwningPlayerPawn());
}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	
}
