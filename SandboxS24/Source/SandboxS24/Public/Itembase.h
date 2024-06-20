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
	UPROPERTY(VisibleAnywhere, Category = "ItemData", meta = (UIMIN = 1, UIMAX 100))
	int32 Quantity; 

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
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
		return ID == OtherID; 
	}
	
};
