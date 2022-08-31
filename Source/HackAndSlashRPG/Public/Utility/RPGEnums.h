// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "RPGEnums.generated.h"

template <typename EnumClass>
int32 static EnumToInt(EnumClass Enum)
{
	return static_cast<int32>(Enum);
}

template <typename EnumClass>
FString static EnumToString(EnumClass Enum)
{
	static const UEnum* EnumToConvert = StaticEnum<EnumClass>();
	return EnumToConvert->GetNameStringByValue(static_cast<int64>(Enum));
}

UENUM(BlueprintType, Blueprintable)
enum class EStat : uint8
{
	Armor              UMETA(DisplayName = "Armor"),
	MaxHealth          UMETA(DisplayName = "MaxHealth"),
	MaxMana            UMETA(DisplayName = "MaxMana"),
	MinDamage          UMETA(DisplayName = "MinDamage"),
	MaxDamage          UMETA(DisplayName = "MaxDamage"),
	DamageMultiplier   UMETA(DisplayName = "DamageMultiplier"),
	AttackSpeed        UMETA(DisplayName = "AttackSpeed"),
	MoveSpeed          UMETA(DisplayName = "MoveSpeed"),
	HealthRegen        UMETA(DisplayName = "HealthRegen"),
	ManaRegen          UMETA(DisplayName = "ManaRegen")


};

UENUM(BlueprintType)
enum class EAttribute : uint8
{
	Strength UMETA(DisplayName = "Strength"),
	Agility  UMETA(DisplayName = "Agility"),
	Intelligence UMETA(DisplayName = "Intelligence"),
	Vitality UMETA(DisplayName = "Vitality")
};

UENUM(BlueprintType, Blueprintable)
enum class EResource : uint8
{
	Health UMETA(DisplayName = "Health"),
	Mana   UMETA(DisplayName = "Mana")
};

UENUM(BlueprintType)
enum class EItemStorage : uint8
{
	Grid UMETA(DisplayName = "Grid"),
	EquipmentSlot UMETA(DisplayName = "EquipmentSlot")
};
