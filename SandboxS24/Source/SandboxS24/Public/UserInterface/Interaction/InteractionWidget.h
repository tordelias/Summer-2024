// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"
struct FInteractableData;
class AMCharacter;
class UTextBlock; 
class UProgressBar; 
/**
 * 
 */
UCLASS()
class SANDBOXS24_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget")
	AMCharacter* PlayerCharacter; 

	void UpdateWidget(const FInteractableData* InteractableData) const; 

protected: 
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget")
	UTextBlock* NameText; 

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget")
	UTextBlock* KeyPressText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget")
	UProgressBar* InteractionProgressBar; 

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget")
	float CurrentInteractionDuration; 

	UFUNCTION(Category = "Interaction Widget")
	float UpdateInteractionProgress(); 

	virtual void NativeOnInitialized() override; 
	virtual void NativeConstruct() override; 
	
};
