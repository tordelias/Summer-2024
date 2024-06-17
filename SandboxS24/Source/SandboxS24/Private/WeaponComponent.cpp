// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "MCharacter.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeaponComponent::AWeaponComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AWeaponComponent::AttachWeapon(AMCharacter* TargetCharacter)
{
		Character1 = TargetCharacter;
	
		// Check that the character is valid, and has no weapon component yet
		if (Character1 == nullptr || Character1->GetInstanceComponents().FindItemByClass<AWeaponComponent>())
		{
			return false;
		}
	
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		Character1->AttachToComponent(Character1->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
		// add the weapon as an instance component to the character
	
		// Set up action bindings
		if (APlayerController* PlayerController = Cast<APlayerController>(Character1->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
				Subsystem->AddMappingContext(FireMappingContext, 1);
			}
	
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				// Fire
				EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWeaponComponent::Fire);
			}
		}
	
		UE_LOG(LogTemp, Warning, TEXT("Hello World"));
		return true;
}

void AWeaponComponent::Fire()
{
	// Check if the weapon is automatic
	if (bIsAutomatic)
	{
		// If automatic, start a timer that fires the weapon every FireRate seconds
		//GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AWeaponComponent::FireWeapon, FireRate, true);
	}
	else
	{
		// If not automatic, just fire the weapon once
		FireWeapon();
	}
}

void AWeaponComponent::FireWeapon()
{
		// Check if the character is valid
	if (Character1 == nullptr)
	{
		return;
	}
	
	// Check if the character has a valid controller
	if (APlayerController* PlayerController = Cast<APlayerController>(Character1->GetController()))
	{
		// Get the camera location and rotation
		FVector CameraLocation;
		FRotator CameraRotation;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
	
		// Calculate the end location of the line trace
		FVector EndLocation = CameraLocation + (CameraRotation.Vector() * Range);
	
		// Perform a line trace to detect any hit actors
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(Character1);
		GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndLocation, ECollisionChannel::ECC_Visibility, CollisionParams);
	
		// Check if the hit actor is valid
		if (HitResult.GetActor())
		{
			// Apply damage to the hit actor
			//HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(), PlayerController, Character1);
		}
	}

}

// Called when the game starts or when spawned
void AWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

