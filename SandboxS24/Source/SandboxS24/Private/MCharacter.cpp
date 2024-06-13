// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
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
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
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


	// enable crouching
	if (GetMovementComponent())
	{
		GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}

}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		InitalCameraRotation = GetMesh()->GetRelativeRotation();
		bUseControllerRotationYaw = false;
		bAltLook = false;
	}
	else
	{
		
		GetFirstPersonCameraComponent()->SetRelativeRotation(InitalCameraRotation);
		GetThirdPersonCameraComponent()->SetRelativeRotation(InitalCameraRotation);
		bUseControllerRotationYaw = true;
		bAltLook = true;
	}
}


