// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemObject.h"

UItemObject::UItemObject()
{
		weight = 1.0f;
		ItemDisplayName = FText::FromString("Item");
		UseActionText = FText::FromString("Use");
}

