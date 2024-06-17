// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItemObject.h"
#include "MCharacter.h"
#include "WeaponComponent.h"


void UWeaponItemObject::Use(AMCharacter* Character)
{
    AWeaponComponent* Weapon = GetWorld()->SpawnActor<AWeaponComponent>();
    if (Weapon)
    {
        Weapon->Damage = Damage;
        Weapon->Range = Range;
        Weapon->FireRate = FireRate;
        Weapon->ReloadTime = ReloadTime;
        Weapon->MaxAmmo = MaxAmmo;
        Weapon->ClipSize = ClipSize;
        Weapon->bIsAutomatic = bIsAutomatic;
        Weapon->bIsProjectile = bIsProjectile;
        Weapon->AttachWeapon(Character);
    }

}


UWeaponItemObject::UWeaponItemObject()
{
	Damage = 10.0f;
	Range = 1000.0f;
	FireRate = 0.1f;
	ReloadTime = 1.0f;
	MaxAmmo = 100;
	ClipSize = 10;
	bIsAutomatic = false;
	bIsProjectile = false;


}
