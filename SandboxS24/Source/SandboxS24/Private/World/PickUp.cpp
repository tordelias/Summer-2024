// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PickUp.h"
#include "Itembase.h"
#include "ItemDataStructs.h"
#include "InventoryComponent.h"
#include "MCharacter.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh"); 
	PickUpMesh->SetSimulatePhysics(true); 
	SetRootComponent(PickUpMesh); 

}
void APickUp::BeginPlay()
{
	Super::BeginPlay();

	//InitalizePickup(UItembase::StaticClass(), ItemQuantity);

}

void APickUp::InitalizePickup(const TSubclassOf<UItembase> BaseClass, const int32 InQuantity)
{
	if (ItemDataTable && !DesieredItemID.IsNone())
	{
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesieredItemID, DesieredItemID.ToString());

		ItemRefrence = NewObject<UItembase>(this, BaseClass);

		ItemRefrence->ID = ItemData->ID; 
		ItemRefrence->ItemType = ItemData->ItemType; 
		ItemRefrence->ItemQuality = ItemData->ItemQuality; 
		ItemRefrence->ItemNumericData = ItemData->ItemNumericData; 
		ItemRefrence->ItemTextData = ItemData->ItemTextData; 
		ItemRefrence->ItemAssetData = ItemData->ItemAssetData; 

		InQuantity <= 0 ? ItemRefrence->SetQuantity(1) : ItemRefrence->SetQuantity(InQuantity); 

		PickUpMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);

		UpdateInteractableData(); 
	}
}

void APickUp::InitalizeDrop(UItembase* ItemDrop, const int32 InQuantity)
{
	ItemRefrence = ItemDrop; 
	InQuantity <= 0 ? ItemRefrence->SetQuantity(1) : ItemRefrence->SetQuantity(InQuantity);
	ItemRefrence->ItemNumericData.Weight = ItemDrop->GetItemSingleWeight(); 
	PickUpMesh->SetStaticMesh(ItemDrop->ItemAssetData.Mesh);
	UpdateInteractableData(); 
}

void APickUp::BeginFocus()
{
	if (PickUpMesh)
	{
		PickUpMesh->SetRenderCustomDepth(true);
	}
}

void APickUp::EndFocus()
{
	if (PickUpMesh)
	{
		PickUpMesh->SetRenderCustomDepth(false);
	}
}

void APickUp::Interact(AMCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		TakePickup(PlayerCharacter);
	}
}

// Called when the game starts or when spawned

void APickUp::TakePickup(const AMCharacter* Taker)
{
	if (IsPendingKillPending())
		return;

	if (!ItemRefrence)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pickup internal item refrence was null"));
		return;
	}

	if (UInventoryComponent* PlayerInventory = Taker->GetInventory())
	{
		const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemRefrence); 
		switch (AddResult.OperationResult)
		{
		case EItemAddResult::IAR_NoItemAdded: 

			break; 
		case EItemAddResult::IAR_PartialAmountItemAdded:

			UpdateInteractableData(); 
			Taker->UpdateInteractionWidget(); 

			break; 

		case EItemAddResult::IAR_AllItemAdded:
			Destroy(); 
			break; 
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Inventory component is null!")); 
	}
}

void APickUp::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = ItemRefrence->ItemTextData.IteractionText;
	InstanceInteractableData.Name = ItemRefrence->ItemTextData.Name; 
	InstanceInteractableData.Quantity = ItemRefrence->Quantity; 
	InteractableData = InstanceInteractableData; 
}

void APickUp::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None; 

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickUp, DesieredItemID))
	{
		if (ItemDataTable)
		{
			if (const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesieredItemID, DesieredItemID.ToString()))
			{
				PickUpMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
			}
		}
	}
}

