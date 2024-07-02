// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Itembase.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}
// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();



}

FItemAddResult UInventoryComponent::HandleNonStackableItems(UItembase* ItemIn, int32 RequestedAddAmount)
{
	//check if item has valid weight 
	if (FMath::IsNearlyZero(ItemIn->GetItemSingleWeight()) || ItemIn->GetItemStackWeight() < 0)
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Item has an invalid weight value."), ItemIn->ItemTextData.Name)); 
	}

	if (InventoryTotalWeight + ItemIn->GetItemSingleWeight() > GetWeightCapacity())
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Item would overflow weight limit"), ItemIn->ItemTextData.Name));
	}
	if (InventoryContents.Num() + 1 > InventorySlotsCapacity)
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. All inventory slots are full"), ItemIn->ItemTextData.Name));
	}

	AddNewItem(ItemIn, RequestedAddAmount);
	return FItemAddResult::AddedAll(RequestedAddAmount,FText::Format(FText::FromString("Successfully added {0} x{1} to the inventory."), ItemIn->ItemTextData.Name, RequestedAddAmount));
}

int32 UInventoryComponent::HandleStackableItems(UItembase* ItemIn, int32 RequestedAddAmount)
{
	return int32();
}

int32 UInventoryComponent::CalculateWeightAddAmount(UItembase* ItemIn, int32 RequestedAddAmount)
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->GetItemSingleWeight()); 
	if (WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount; 
	}
	return WeightMaxAddAmount; 
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItembase* StackableItem, int32 InitalRequestedAddAmount)
{
	const int32 AddAmountToMakeFullStack = StackableItem->ItemNumericData.MaxStackSize - StackableItem->Quantity; 

	return FMath::Min(InitalRequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::AddNewItem(UItembase* Item, const int32 AmountToAdd)
{
	UItembase* NewItem; 
	if (Item->bIsCopy || Item->bIsPickup)
	{
		NewItem = Item; 
		NewItem->ResetItemFlags(); 
	}
	else
	{
		NewItem = Item->CreateItemCopy();
	}
	NewItem->OwningInventory = this; 
	NewItem->SetQuantity(AmountToAdd);

	InventoryContents.Add(NewItem); 
	InventoryTotalWeight += NewItem->GetItemStackWeight();
	OnInventoryUpdated.Broadcast(); 
}

FItemAddResult UInventoryComponent::HandleAddItem(UItembase* InputItem)
{
	if (GetOwner())
	{
		const int32 InitalRequestedAddAmount = InputItem->Quantity; 

		//Non Stackable
		if (!InputItem->ItemNumericData.bIsStackable)
		{
			return HandleNonStackableItems(InputItem, InitalRequestedAddAmount); 
		}

		//Stackable
		//const int32 StackableAmountAdded = HandleStackableItems(InputItem, InitalRequestedAddAmount); 
		//if (StackableAmountAdded == InitalRequestedAddAmount)
		//{
		//	//return added all result
		//}
		//if (StackableAmountAdded < InitalRequestedAddAmount && StackableAmountAdded > 0)
		//{
		//	//return added partial result
		//}
		//if (StackableAmountAdded <= 0)
		//{
		//	//return added none result
		//}

		//Temprary return to compile
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Item has an invalid weight value."), InputItem->ItemTextData.Name));
	}
	//Temprary return to compile
	return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Item has an invalid weight value."), InputItem->ItemTextData.Name));
}

UItembase* UInventoryComponent::FindMatchingItem(UItembase* ItemIn) const
{
	if (ItemIn)
	{
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn; 
		}
	}
	return nullptr; 
}

UItembase* UInventoryComponent::FindNextItemByID(UItembase* ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray<TObjectPtr<UItembase>>::ElementType* Result = InventoryContents.FindByPredicate([&ItemIn](const UItembase* InventoryItem)
			{
				return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsFullStack();
			}
		))
		{
			return *Result; 
		}
	}
	return nullptr;
}

UItembase* UInventoryComponent::FindNextPartialStack(UItembase* ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray<TObjectPtr<UItembase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
	return nullptr;
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItembase* ItemToRemove)
{
	InventoryContents.RemoveSingle(ItemToRemove);
	OnInventoryUpdated.Broadcast(); 
}

int32 UInventoryComponent::RemoveAmountOfItem(UItembase* ItemIn, int32 DesiredAmountToRemove)
{
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmountToRemove, ItemIn->Quantity);
	ItemIn->SetQuantity(ItemIn->Quantity - ActualAmountToRemove); 

	InventoryTotalWeight -= ActualAmountToRemove * ItemIn->GetItemSingleWeight(); 
	OnInventoryUpdated.Broadcast(); 

	return ActualAmountToRemove; 
}

void UInventoryComponent::SplitExistingStack(UItembase* ItemIn, int32 AmountToSplit)
{
	if (!(InventoryContents.Num() + 1 > InventorySlotsCapacity))
	{
		RemoveAmountOfItem(ItemIn, AmountToSplit); 
		AddNewItem(ItemIn, AmountToSplit); 
	}
}







