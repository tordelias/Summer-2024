// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemDataStructs.h"
#include "Itembase.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXS24_API UItembase : public UObject
{
	GENERATED_BODY()


public: 

	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	/** Amount of items in a stack */
	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 Quantity; 

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData ItemNumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData ItemAssetData;

	UItembase(); 

	UItembase* CreateItemCopy() const;

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * ItemNumericData.Weight;}
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return ItemNumericData.Weight; }

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullStack() const { return Quantity == ItemNumericData.MaxStackSize; }

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	virtual void Use(ACharacter* Character);

protected: 
	bool operator == (const FName& OtherID) const
	{
		return this->ID == OtherID; 
	}
	
};
