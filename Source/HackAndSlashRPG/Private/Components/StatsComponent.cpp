// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Components/StatsComponent.h"

UStatsComponent::UStatsComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStatsComponent::AddHealth(const float Health)
{
	BaseStats.MaxHealth += Health;
	
	const float HealthRatio = CurrentStats.CurrentHealth / CurrentStats.MaxHealth;
	
	CurrentStats.MaxHealth += Health;

	CurrentStats.CurrentHealth = HealthRatio * CurrentStats.MaxHealth;

	ApplyEffects();

	OnHealthChange.Broadcast(CurrentStats.CurrentHealth, CurrentStats.MaxHealth);
}

void UStatsComponent::AddMana(const float Mana)
{
	BaseStats.MaxMana += Mana;

	const float ManaRatio = CurrentStats.CurrentMana / CurrentStats.MaxMana;

	CurrentStats.MaxMana += Mana;

	CurrentStats.CurrentMana = ManaRatio * CurrentStats.MaxMana;

	ApplyEffects();

	OnManaChange.Broadcast(CurrentStats.CurrentMana, CurrentStats.MaxMana);
}

void UStatsComponent::AddAttackCooldown(const float AttackCooldown)
{
	BaseStats.AttackCooldown += AttackCooldown;

	ApplyEffects();

	OnStatsChange.Broadcast(CurrentStats);
}

void UStatsComponent::AddDamage(const float Damage)
{
	BaseStats.Damage += Damage;

	ApplyEffects();

	OnStatsChange.Broadcast(CurrentStats);
}

void UStatsComponent::AddDamageMultiplier(const float DamageMultiplier)
{
	BaseStats.DamageMultiplier += DamageMultiplier;

	ApplyEffects();

	OnStatsChange.Broadcast(CurrentStats);
}

void UStatsComponent::AddDefenseMultiplier(const float DefenseMultiplier)
{
	BaseStats.DefenseMultiplier += DefenseMultiplier;

	ApplyEffects();

	OnStatsChange.Broadcast(CurrentStats);
}

void UStatsComponent::ApplyEffects()
{
	
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

