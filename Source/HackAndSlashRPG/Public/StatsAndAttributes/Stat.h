// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Stat.generated.h"

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

int32 static StatToInt(EStat Stat)
{
	return static_cast<int32>(Stat);
}


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeStat, float, NewValue);

/**
 * RPG stat ie armor, damage etc. 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class HACKANDSLASHRPG_API UStat : public UObject
{
	GENERATED_BODY()
public:
	UStat();

	static UStat* Create(float InInitialValue, EStat InType, FText InName,
		float InMinValue = TNumericLimits<float>::Min(), float InMaxValue = TNumericLimits<float>::Max());

	UFUNCTION(BlueprintPure)
	float Get()const { return ClampedValue; }

	/** Call only from modificators */
	UFUNCTION(BlueprintCallable)
	void AddChange(float Value);
	// TODO: make private, friend modificator class
	/** Call only from modificators */
	UFUNCTION(BlueprintCallable)
	void RemoveChange(float Value);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnChangeStat OnChange;

protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
private:
	void SetInitialValue(float InInitialValue);
	
	/** To prevent modificators from removing more value than needed */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float OverflowValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ClampedValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InitialValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxValue = TNumericLimits<float>::Max();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MinValue = TNumericLimits<float>::Min();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EStat Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText Name;
};

