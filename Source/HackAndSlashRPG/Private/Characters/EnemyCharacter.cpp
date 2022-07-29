// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "StatsAndAttributes/Resource.h"
#include "StatsAndAttributes/Stat.h"
#include "StatsAndAttributes/StatCollection.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1/*MouseCursor*/, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCapsuleSize(50.f, 88.f);
	GetCapsuleComponent()->OnBeginCursorOver.AddDynamic(this, &AEnemyCharacter::OnMouseEnter);
	GetCapsuleComponent()->OnEndCursorOver.AddDynamic(this, &AEnemyCharacter::OnMouseLeft);

	TargetDecal = CreateDefaultSubobject<UDecalComponent>("TargetDecal");
	TargetDecal->DecalSize = FVector(16.f, 32.f, 32.f);
	TargetDecal->SetVisibility(false);
	TargetDecal->SetupAttachment(RootComponent);
	TargetDecal->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	TargetDecal->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}

#if WITH_EDITOR

void AEnemyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentArmor))
	{
		GetStat(EStat::Armor)->SetValue(CurrentArmor);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentAttackSpeed))
	{
		GetStat(EStat::AttackSpeed)->SetValue(CurrentAttackSpeed);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentMaxHealth))
	{
		GetStat(EStat::MaxHealth)->SetValue(CurrentMaxHealth);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentMaxMana))
	{
		GetStat(EStat::MaxMana)->SetValue(CurrentMaxMana);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentDamageMultiplier))
	{
		GetStat(EStat::DamageMultiplier)->SetValue(CurrentDamageMultiplier);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentHealthRegen))
	{
		GetStat(EStat::HealthRegen)->SetValue(CurrentHealthRegen);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentManaRegen))
	{
		GetStat(EStat::ManaRegen)->SetValue(CurrentManaRegen);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentMaxDamage))
	{
		GetStat(EStat::MaxDamage)->SetValue(CurrentMaxDamage);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentMinDamage))
	{
		GetStat(EStat::MinDamage)->SetValue(CurrentMinDamage);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentMoveSpeed))
	{
		GetStat(EStat::MoveSpeed)->SetValue(CurrentMoveSpeed);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentHealth))
	{
		GetResource(EResource::Health)->SetValue(CurrentHealth);
	}
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemyCharacter, CurrentMana))
	{
		GetResource(EResource::Mana)->SetValue(CurrentMana);
	}
}

#endif // WITH_EDITOR

void AEnemyCharacter::PostInitProperties()
{
	Super::PostInitProperties();

	// the order matters here
	ConfigureStatCallbacks();
	SetInitialValues();

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();


}

void AEnemyCharacter::OnMouseEnter(UPrimitiveComponent* TouchedComponent)
{
	TargetDecal->SetVisibility(true);
}

void AEnemyCharacter::OnMouseLeft(UPrimitiveComponent* TouchedComponent)
{
	TargetDecal->SetVisibility(false);
}

void AEnemyCharacter::SetInitialValues()
{
	UStatCollection* Stats = GetStats();

	checkf(Stats, TEXT("Stats not valid"))

	GetStat(EStat::Armor)->SetInitialValue(InitialArmor);
	GetStat(EStat::MaxMana)->SetInitialValue(InitialMaxMana);
	GetStat(EStat::AttackSpeed)->SetInitialValue(InitialAttackSpeed);
	GetStat(EStat::DamageMultiplier)->SetInitialValue(InitialDamageMultiplier);
	GetStat(EStat::HealthRegen)->SetInitialValue(InitialHealthRegen);
	GetStat(EStat::ManaRegen)->SetInitialValue(InitialManaRegen);
	GetStat(EStat::MaxDamage)->SetInitialValue(InitialMaxDamage);
	GetStat(EStat::MinDamage)->SetInitialValue(InitialMinDamage);
	GetStat(EStat::MaxHealth)->SetInitialValue(InitialMaxHealth);
	GetStat(EStat::MoveSpeed)->SetInitialValue(InitialMoveSpeed);

	UResource* HealthResource = GetResource(EResource::Health);
	GetStat(EStat::MaxHealth)->OnChange.AddUObject(HealthResource, &UResource::OnDependentStatChange);
	HealthResource->OnDependentStatChange(InitialMaxHealth);
	HealthResource->SetValue(InitialHealth);

	UResource* ManaResource = GetResource(EResource::Mana);
	GetStat(EStat::MaxMana)->OnChange.AddUObject(ManaResource, &UResource::OnDependentStatChange);
	ManaResource->OnDependentStatChange(InitialMaxMana);
	ManaResource->SetValue(InitialMana);
}

void AEnemyCharacter::ConfigureStatCallbacks()
{
	UStatCollection* Stats = GetStats();
	checkf(Stats, TEXT("Stats not valid"))

	GetStat(EStat::Armor)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentArmor);
	GetStat(EStat::MaxMana)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentMaxMana);
	GetStat(EStat::AttackSpeed)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentAttackSpeed);
	GetStat(EStat::DamageMultiplier)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentDamageMultiplier);
	GetStat(EStat::HealthRegen)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentHealthRegen);
	GetStat(EStat::ManaRegen)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentManaRegen);
	GetStat(EStat::MaxDamage)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentMaxDamage);
	GetStat(EStat::MinDamage)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentMinDamage);
	GetStat(EStat::MaxHealth)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentMaxHealth);
	GetStat(EStat::MoveSpeed)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentMoveSpeed);

	GetResource(EResource::Health)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentHealth);
	GetResource(EResource::Mana)->OnChange.AddUObject(this, &AEnemyCharacter::SetCurrentMana);
}
