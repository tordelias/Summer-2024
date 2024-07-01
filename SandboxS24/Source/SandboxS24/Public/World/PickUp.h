// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "PickUp.generated.h"

class UItembase;
class UDataTable; 

UCLASS()
class SANDBOXS24_API APickUp : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();



	void InitalizePickup(const TSubclassOf<UItembase> BaseClass, const int32 InQuantity);

	void InitalizeDrop(UItembase* ItemDrop, const int32 InQuantity);

	FORCEINLINE UItembase* GetItemData() { return ItemRefrence; }

	virtual void BeginFocus() override; 

	virtual void EndFocus() override; 

	virtual void Interact(AMCharacter* PlayerCharacter) override; 



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	UStaticMeshComponent* PickUpMesh; 

	UPROPERTY(EditInstanceOnly, Category = "Pickup")
	UDataTable* ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Pickup")
	FName DesieredItemID;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	UItembase* ItemRefrence;

	UPROPERTY(EditInstanceOnly, Category = "Pickup")
	int32 ItemQuantity;

	UPROPERTY(VisibleInstanceOnly, Category = "Pickup")
	FInteractableData InstanceInteractableData;


	void TakePickup(const AMCharacter* Taker);

	void UpdateInteractableData(); 

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override; 
#endif

};
