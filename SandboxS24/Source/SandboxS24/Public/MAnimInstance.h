// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SandboxS24/SandboxS24.h"
#include "MAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXS24_API UMAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties", meta = (AllowPrivateAccess = "true"))
	class AMCharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	EWeaponType WeaponBeingUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	float speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	bool bIsAlive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	bool bIsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Functions")
	bool bDoOnce;

	UFUNCTION(BlueprintCallable, Category = "Animations")
	virtual void UpdateAnimationProperties();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void ResetCanAttack();

	UFUNCTION()
	void DoOnce();

	UFUNCTION()
	void ResetDoOnce();
};
