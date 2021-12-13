// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMana = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackCooldown = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefenseMultiplier = 0.f;

	FCharacterStats()
	{
		CurrentHealth = MaxHealth;
		CurrentMana = MaxMana;
	}

	static FCharacterStats GetDefaultStats()
	{
		static FCharacterStats DefaultStats = FCharacterStats();
		return DefaultStats;
	}
};

USTRUCT()
struct FStatLimits
{
	GENERATED_BODY()

	float MaxAttackCooldown = 2.f;
	float MinAttackCooldown = 0.25f;

	float MinDamage = 1.f;
	float MinDamageMultiplier = 0.1f;

	float MinDefenseMultiplier = -0.5f;
	float MaxDefenseMultiplier = 0.85f;

	static FStatLimits GetLimits()
	{
		static FStatLimits Limits = FStatLimits();
		return Limits;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, const float, CurrentHealth, const float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChange, const float, CurrentMana, const float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatsChange, const FCharacterStats&, CurrentStats);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASHRPG_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatsComponent();

	FCharacterStats GetStats()const { return CurrentStats; }
	FCharacterStats GetBaseStats()const { return BaseStats; }

	void AddHealth(const float Health);
	void AddMana(const float Mana);
	void AddAttackCooldown(const float AttackCooldown);
	void AddDamage(const float Damage);
	void AddDamageMultiplier(const float DamageMultiplier);
	void AddDefenseMultiplier(const float DefenseMultiplier);

	void ApplyEffects();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnHealthChange OnHealthChange;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnManaChange OnManaChange;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnStatsChange OnStatsChange;
	
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	/** Stats that initialize character with base values */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FCharacterStats BaseStats;

	/** All changes (buffs, debuffs, etc.) applied to these stats. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FCharacterStats CurrentStats;
	
};
