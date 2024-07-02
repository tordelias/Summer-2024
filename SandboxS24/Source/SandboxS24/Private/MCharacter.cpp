// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "MCharacter.h"
#include "HUD_BaseSetup.h"
#include "Interfaces/InteractionInterface.h"
#include "InventoryComponent.h"

//Engine
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/LocalPlayer.h"

//Debug
#include "DrawDebugHelpers.h"


// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(5.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bUsePawnControlRotation = true; 

	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(SpringArm);
	//ThirdPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera	bUseControllerRotationYaw = false; 

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->SetupAttachment(SpringArm);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	//inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	InventoryComponent->SetSlotsCapacity(20);
	InventoryComponent->SetrWeightCapasity(50.f);

	// enable crouching
	if (GetMovementComponent())
	{
		GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}

	WeaponBeingUsed= EWeaponType::EWT_None;

	// the frequency PerformInteractionCheck() will run, so it dosen't run every frame
	InteractionCheckFrequency = 0.1f; 

	InteractionCheckDistance = 225.f; 
}



// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	HUD_BaseSetup = Cast<AHUD_BaseSetup>(GetWorld()->GetFirstPlayerController()->GetHUD());

}


// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}

}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMCharacter::LookFp);

		//Switch Camera
		EnhancedInputComponent->BindAction(IA_SwitchCamera, ETriggerEvent::Triggered, this, &AMCharacter::SwitchCamera);

		//AltLook
		EnhancedInputComponent->BindAction(IA_AltLook, ETriggerEvent::Started, this, &AMCharacter::AltLook);
		EnhancedInputComponent->BindAction(IA_AltLook, ETriggerEvent::Completed, this, &AMCharacter::AltLook);

		//Crouch
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AMCharacter::Crouch);
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AMCharacter::CrouchEnd);

		//Run
		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Started, this, &AMCharacter::Run);
		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &AMCharacter::StopRunning);

		//Open Inventory
		EnhancedInputComponent->BindAction(IA_Inventory, ETriggerEvent::Started, this, &AMCharacter::OpenInventory);

		//Interact
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AMCharacter::BeginInteract);
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Completed, this, &AMCharacter::EndInteract);
	}

}


void AMCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMCharacter::LookFp(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMCharacter::LookTp(const FInputActionValue& Value)
{
}

void AMCharacter::SwitchCamera()
{
	if (bSwitchCamera)
	{
		//UE_LOG(MyLogCategory, Error, TEXT("An error occurred in SomeFunction: %s"), TEXT("Detailed error message"));
		bSwitchCamera = false; 
		GetThirdPersonCameraComponent()->SetActive(true); 
		GetFirstPersonCameraComponent()->SetActive(false);
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		
	}
	else
	{
		bSwitchCamera = true; 
		GetFirstPersonCameraComponent()->SetActive(true);
		GetThirdPersonCameraComponent()->SetActive(false);
		bUseControllerRotationYaw = true; 
		GetCharacterMovement()->bOrientRotationToMovement = true; 
	}
}

void AMCharacter::Run(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;

}

void AMCharacter::StopRunning(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AMCharacter::Crouch(const FInputActionValue& Value)
{
	GetCharacterMovement()->bWantsToCrouch = true; 

}

void AMCharacter::CrouchEnd(const FInputActionValue& Value)
{
	GetCharacterMovement()->bWantsToCrouch = false;
}

void AMCharacter::AltLook(const FInputActionValue& Value)
{
	if(bAltLook)
	{
		InitalCameraRotation = GetControlRotation();
		bUseControllerRotationYaw = false;
		bAltLook = false;
	}
	else
	{
		GetController()->SetControlRotation(InitalCameraRotation);
		bUseControllerRotationYaw = true;
		bAltLook = true;
	}
}

void AMCharacter::OpenInventory()
{
	// Get the player controller
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		// Get the HUD and cast it to AHUD_BaseSetup
		//AHUD_BaseSetup* HUD = Cast<AHUD_BaseSetup>(PlayerController->GetHUD());
		if (HUD_BaseSetup)
		{
			// Now it's safe to call WantsToOpenWidget
			HUD_BaseSetup->WantsToOpenWidget(2);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to cast to AHUD_BaseSetup in OpenInventory"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is null in OpenInventory"));
	}
}

void AMCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds(); 
	FVector TraceStart{GetPawnViewLocation()};
	FVector TraceEnd{ TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance) };
	float ViewDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());

	if(ViewDirection > 0)
	{
		//DebugLine to see LineTrace
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0.5f, 0, 2.f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;

		if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
		{
			if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{

				if (TraceHit.GetActor() != InteractionData.CurrentInteractable)
				{
					FoundInteractable(TraceHit.GetActor());
					return;
				}
				else
				{
					return;

				}
			}
		}
	}
	NoInteractableFound();
}

void AMCharacter::FoundInteractable(AActor* newInteractable)
{
	if (bIsInteracting())
	{
		EndInteract();
	}
	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus(); 
	}

	InteractionData.CurrentInteractable = newInteractable;
	TargetInteractable = newInteractable;

	HUD_BaseSetup->UpdateInteractionWidget(&TargetInteractable->InteractableData);

	TargetInteractable->BeginFocus();
}

void AMCharacter::NoInteractableFound()
{
	if (bIsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandleInteraction);
	}
	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		HUD_BaseSetup->HideInteractionWidget();

		InteractionData.CurrentInteractable = nullptr; 
		TargetInteractable = nullptr; 
	}
}

void AMCharacter::BeginInteract()
{
	PerformInteractionCheck();
	
	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();
			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandleInteraction, this, &AMCharacter::Interact, TargetInteractable->InteractableData.InteractionDuration, false);
			}
		}

	}
}

void AMCharacter::EndInteract()
{
		GetWorldTimerManager().ClearTimer(TimerHandleInteraction);

		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndInteract();
		}
}

void AMCharacter::Interact()
{

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}

void AMCharacter::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		HUD_BaseSetup->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}

}


