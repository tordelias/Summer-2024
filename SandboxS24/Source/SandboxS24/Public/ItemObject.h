// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS(Abstract,BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class SANDBOXS24_API UItemObject : public UObject
{
	GENERATED_BODY()
	
	public:

	// Constructor
	UItemObject(); 
	virtual class UWorld* GetWorld() const { return World;  };
	UPROPERTY(Transient)
	class UWorld* World;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float weight; 

	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	virtual void Use(class AMCharacter* Character) PURE_VIRTUAL(UItemObject, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AMCharacter* Character);
};
