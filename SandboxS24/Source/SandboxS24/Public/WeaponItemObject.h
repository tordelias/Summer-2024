// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponItemObject.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXS24_API UWeaponItemObject : public UItemObject
{
	GENERATED_BODY()

	UWeaponItemObject();

	public:
		virtual void Use(class AMCharacter* Character) override;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float Damage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float Range;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float FireRate;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float ReloadTime;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int32 MaxAmmo;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int32 ClipSize;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool bIsAutomatic;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool bIsProjectile;


		/** Sets default values for this component's properties */

		/** Attaches the actor to a FirstPersonCharacter */
		//UFUNCTION(BlueprintCallable, Category = "Weapon")
		//bool AttachWeapon(AMCharacter* TargetCharacter);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		//TSubclassOf<AActor> ProjectileClass;
	
private: 

};
