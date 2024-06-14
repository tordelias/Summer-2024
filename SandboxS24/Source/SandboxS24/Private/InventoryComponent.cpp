// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemObject.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Capacity = 20; 
}

bool UInventoryComponent::AddItem(UItemObject* Item)
{
	if(Items.Num() >= Capacity || !Item)
	{
		return false;
	}
	//adds item to inventory
	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);
	//broadcasts that the inventory has been updated / refreshes the inventory
	OnInventoryUpdated.Broadcast();
	return true;
}

bool UInventoryComponent::RemoveItem(UItemObject* Item)
{
	if(Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		//broadcasts that the inventory has been updated / refreshes the inventory
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for(auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
	
}

