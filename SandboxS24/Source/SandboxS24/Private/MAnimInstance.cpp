// Fill out your copyright notice in the Description page of Project Settings.


#include "MAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MCharacter.h"
#include "Kismet/GameplayStatics.h"

UMAnimInstance::UMAnimInstance()
{
	bDoOnce = true;
	bIsAlive = true;
	bIsFalling = false;
	//TODO is fireing bool?
	WeaponBeingUsed = EWeaponType::EWT_None;
}

void UMAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<AMCharacter>(TryGetPawnOwner());
}

void UMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Character)
	{
		UpdateAnimationProperties();
	}
	else
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMCharacter::StaticClass(), FoundActors);
		for (AActor* Actor : FoundActors)
		{
			Character = Cast<AMCharacter>(Actor);
			if (Character)
			{
				UpdateAnimationProperties();
				break;
			}
		}
	}
}

void UMAnimInstance::UpdateAnimationProperties()
{
	speed = Character->GetVelocity().Size();
	bIsFalling = Character->GetMovementComponent()->IsFalling();
	//bIsAlive = Character->IsPlayerAlive(); //TODO ADD THIS ON CHARACTER
	bIsAlive = true; //TODO Remove once above is added
	WeaponBeingUsed = Character->GetWeaponBeingUsed(); //TODO Make sure this is set up in character once more weapons is added
}

void UMAnimInstance::ResetCanAttack()
{
	//For example dogding
	//Character->SetplayerCanDogdge(true);
	//Not used yet
}

void UMAnimInstance::DoOnce()
{
	if (bDoOnce)
	{
		// do things here
	}
}

void UMAnimInstance::ResetDoOnce()
{
	bDoOnce = true;
}
