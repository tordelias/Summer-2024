// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated); 

class UItembase;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No item added"),
	IAR_PartialAmountItemAdded UMETA(DisplayName = "Partial amount of item added"),
	IAR_AllItemAdded UMETA(DisplayName = "All of item added")
};


USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_USTRUCT_BODY()

	FItemAddResult() : ActualAmountAdded(0), OperationResult(EItemAddResult::IAR_NoItemAdded), ResultMessage(FText::GetEmpty()) {};


	//Actual amount of items added to the inventory
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountAdded;

	// Enum representing the end state of an add item operation
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;

	// Informational message that can be passed with the resault 
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ResultMessage; 

	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResault; 
		AddedNoneResault.ActualAmountAdded = 0; 
		AddedNoneResault.OperationResult = EItemAddResult::IAR_NoItemAdded; 
		AddedNoneResault.ResultMessage = ErrorText; 
		return AddedNoneResault; 
	};

	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText) 
	{
		FItemAddResult AddedPartialResault;
		AddedPartialResault.ActualAmountAdded = PartialAmountAdded;
		AddedPartialResault.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialResault.ResultMessage = ErrorText;
		return AddedPartialResault;

	};

	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message)
	{
		FItemAddResult AddedAllResault;
		AddedAllResault.ActualAmountAdded = AmountAdded;
		AddedAllResault.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedAllResault.ResultMessage = Message;
		return AddedAllResault;

	};


};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOXS24_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	FOnInventoryUpdated OnInventoryUpdated; 


	UFUNCTION(Category = "Inventory")
	FItemAddResult HandleAddItem(UItembase* InputItem);
	
	UFUNCTION(Category = "Inventory")
	UItembase* FindMatchingItem(UItembase* ItemIn) const;

	UFUNCTION(Category = "Inventory")
	UItembase* FindNextItemByID(UItembase* ItemIn) const; 

	UFUNCTION(Category = "Inventory")
	UItembase* FindNextPartialStack(UItembase* ItemIn) const; 

	UFUNCTION(Category = "Inventory")
	void RemoveSingleInstanceOfItem(UItembase* ItemToRemove);

	UFUNCTION(Category = "Inventory")
	int32 RemoveAmountOfItem(UItembase* ItemIn, int32 DesiredAmountToRemove); 

	UFUNCTION(Category = "Inventory")
	void SplitExistingStack(UItembase* ItemIn, int32 AmountToSplit); 


	UFUNCTION(Category = "Inventory")
	FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; };

	UFUNCTION(Category = "Inventory")
	FORCEINLINE float GetWeightCapacity() const { return InventoryWeightCapacity; };

	UFUNCTION(Category = "Inventory")
	FORCEINLINE int32 GetSlotsCapacity() const { return InventorySlotsCapacity; };

	UFUNCTION(Category = "Inventory")
	FORCEINLINE TArray<UItembase*> GetInventoryContents() const { return InventoryContents;  };

	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) { InventorySlotsCapacity = NewSlotsCapacity;  };

	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetrWeightCapasity(const float NewWeightCapasity) { InventoryWeightCapacity = NewWeightCapasity; };


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight; 
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotsCapacity; 
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	float InventoryWeightCapacity; 

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItembase>> InventoryContents; 


	FItemAddResult HandleNonStackableItems(UItembase* ItemIn, int32 RequestedAddAmount); 
	int32 HandleStackableItems(UItembase* ItemIn, int32 RequestedAddAmount);
	int32 CalculateWeightAddAmount(UItembase* ItemIn, int32 RequestedAddAmount);
	int32 CalculateNumberForFullStack(UItembase* StackableItem, int32 InitalRequestedAddAmount); 

	void AddNewItem(UItembase* Item, const int32 AmountToAdd); 

public:	

		
};
