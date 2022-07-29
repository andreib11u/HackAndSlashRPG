// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerAttribute.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttributeChange, int32);

UENUM(BlueprintType)
enum class EAttribute : uint8
{
	Strength UMETA(DisplayName = "Strength"),
	Agility  UMETA(DisplayName = "Agility"),
	Intelligence UMETA(DisplayName = "Intelligence"),
	Vitality UMETA(DisplayName = "Vitality")
};

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UPlayerAttribute : public UObject
{
	GENERATED_BODY()
public:
	static UPlayerAttribute* Create(int32 InValue, FText InName, EAttribute InType);

	int32 Get()const { return Value; }
	void SetValue(int32 InValue);
	void ChangeValue(int32 InValue);

	FOnAttributeChange OnAttributeChange;
private:
	UPROPERTY(VisibleAnywhere)
	int32 Value = 10;

	UPROPERTY(VisibleAnywhere)
	EAttribute Type;

	UPROPERTY(VisibleAnywhere)
	FText Name;
};
