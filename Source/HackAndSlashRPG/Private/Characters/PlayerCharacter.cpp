// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));

	SpringArm->TargetArmLength = 800.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	
	TopDownCamera->SetupAttachment(SpringArm);

	auto CharacterMovementComponent = Cast<UCharacterMovementComponent>(ACharacter::GetMovementComponent());
	bUseControllerRotationYaw = false;
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->RotationRate = FRotator(0.f, 1000.f, 0.f);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::PostInitProperties()
{
	Super::PostInitProperties();

	ApplyAttributes();
}

void APlayerCharacter::ApplyAttributes()
{
	// Vitality
	
	const float HealthRatio = InternalStats.Health / InternalStats.MaxHealth;
	InternalStats.MaxHealth = FInternalStats::GetDefaultStats().MaxHealth + (Attributes.HpPerVitality * Attributes.Vitality);
	InternalStats.Health = HealthRatio * InternalStats.MaxHealth;

	// Intelligence
	
	const float ManaRatio = InternalStats.Mana / InternalStats.MaxMana;
	InternalStats.MaxMana = FInternalStats::GetDefaultStats().MaxMana + (Attributes.MpPerIntelligence * Attributes.Intelligence);
	InternalStats.Mana = ManaRatio * InternalStats.MaxMana;

	// Agility
	
	InternalStats.AttackCooldown = FMath::Clamp(FInternalStats::GetDefaultStats().AttackCooldown - (Attributes.CooldownReductionPerAgility * Attributes.Agility),
		FInternalStats::GetDefaultStats().MinAttackCooldown, BIG_NUMBER);

	// Strength
	
	InternalStats.DamageMultiplier = FMath::Clamp(FInternalStats::GetDefaultStats().DamageMultiplier + (Attributes.DmgPerStrength * Attributes.Strength),
		FInternalStats::GetDefaultStats().MinDamageMultiplier, BIG_NUMBER);
}
