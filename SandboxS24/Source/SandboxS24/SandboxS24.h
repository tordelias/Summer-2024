// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_None UMETA(DisplayName = "None"),
	EWT_Gun UMETA(DisplayName = "Gun"),
	EWT_JetPack UMETA(DisplayName = "JetPack")
};
