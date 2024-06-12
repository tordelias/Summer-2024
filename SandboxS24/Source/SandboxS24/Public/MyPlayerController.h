// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"
class UInputMappingContext; 
/**
 * 
 */
UCLASS()
class SANDBOXS24_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;
	
protected:
	virtual void BeginPlay();

};
