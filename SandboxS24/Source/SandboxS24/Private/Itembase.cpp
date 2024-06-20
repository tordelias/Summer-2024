// Fill out your copyright notice in the Description page of Project Settings.


#include "Itembase.h"
#include "InventoryComponent.h"

UItembase::UItembase()
{
}

UItembase* UItembase::CreateItemCopy() const
{
	UItembase* ItemCopy = NewObject<UItembase>(StaticClass());

	ItemCopy->ID = this->ID; 
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemQuality = this->ItemQuality; 
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->ItemNumericData = this->ItemNumericData; 
	ItemCopy->ItemStatistics = this->ItemStatistics; 
	ItemCopy->ItemAssetData = this->ItemAssetData; 

	return ItemCopy; 
}

void UItembase::SetQuantity(const int32 NewQuantity)
{
	// if stackable uses maxstacksize, if item is not stackable uses 1
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemNumericData.bIsStackable ? ItemNumericData.MaxStackSize : 1);

		if (OwningInventory)
		{
			if (Quantity <= 0)
			{
				//OwningInventory->RemoveItem(this);
			}
		}
	}
}

void UItembase::Use(ACharacter* Character)
{
}
