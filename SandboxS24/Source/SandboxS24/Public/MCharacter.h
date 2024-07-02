// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD_BaseSetup.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SandboxS24/SandboxS24.h"
#include "MCharacter.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class USpringArmComponent;
class UInventoryComponent;
class IInteractionInterface;
struct FInputActionValue;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{

	};


	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime; 
};



UCLASS(config = Game)
class SANDBOXS24_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();

	// Set keybinds 

/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Third person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

private:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Jump;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move;

	/** LookFP Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Look;

	/** SwitchCamera Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_SwitchCamera;

	/** Run Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Run;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Crouch;

	/** AltLook Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_AltLook;

	/** Open Inventory Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Inventory;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Interact;

public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	EWeaponType WeaponBeingUsed;



private:
	// Makes character move
	void Move(const FInputActionValue& Value);

	// Makes character turn/look around in first person
	void LookFp(const FInputActionValue& Value);

	// Makes character turn/look around in third person
	void LookTp(const FInputActionValue& Value);

	// switches between third and first person camera
	void SwitchCamera();

	// makes charecter run
	void Run(const FInputActionValue& Value);
	void StopRunning(const FInputActionValue& Value);

	// makes charecter crouch
	void Crouch(const FInputActionValue& Value);
	void CrouchEnd(const FInputActionValue& Value);

	//Look around without character moving
	void AltLook(const FInputActionValue& Value);

	/**Open Inventory */
	void OpenInventory();

	bool bSwitchCamera = true; 
	bool bAltLook = true; 


	FRotator InitalCameraRotation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AHUD_BaseSetup* HUD_BaseSetup;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable; 

	float InteractionCheckFrequency; 

	float InteractionCheckDistance; 

	FTimerHandle TimerHandleInteraction; 

	FInteractionData InteractionData; 

	void PerformInteractionCheck();
	
	void FoundInteractable(AActor* newInteractable);

	void NoInteractableFound();
	
	void BeginInteract();

	void EndInteract();

	void Interact();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateInteractionWidget() const; 

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UCameraComponent* GetThirdPersonCameraComponent() const { return ThirdPersonCameraComponent; }

	USpringArmComponent* GetSpringArm() const { return SpringArm; }

	EWeaponType GetWeaponBeingUsed() const { return WeaponBeingUsed; }
	FORCEINLINE UInventoryComponent* GetInventory() const { return InventoryComponent;  }


	FORCEINLINE bool bIsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandleInteraction); }


};
