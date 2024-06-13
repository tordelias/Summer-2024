// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_BaseSetup.h"

#include "Blueprint/UserWidget.h"

void AHUD_BaseSetup::BeginPlay()
{
	Super::BeginPlay();

	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());



}

void AHUD_BaseSetup::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

}
