// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/BaseCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/AbilityComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StatsComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));

	StatsComponent = CreateDefaultSubobject<UStatsComponent>("CharacterStats");
}

void ABaseCharacter::StartRotating(const FVector Target, const float RotationSpeed, bool StopWhenFaceTarget)
{
	bIsRotating = true;
	
	const FVector DiffVector = Target - GetActorLocation();
	const FRotator LookAtRotation = FRotator(0.f, DiffVector.Rotation().Yaw, 0.f);
	
	RotationState = FRotationState{ LookAtRotation, StopWhenFaceTarget, RotationSpeed };
}

void ABaseCharacter::StopRotating()
{
	bIsRotating = false;
	RotationState = FRotationState();
	OnRotationEnd.Broadcast();
}

void ABaseCharacter::StartAttackCooldown()
{
	if (GetWorld())
	{
		bIsAttackInCooldown = true;
		GetWorld()->GetTimerManager().SetTimer(AttackCooldownTimerHandle,this, &ABaseCharacter::OnAttackCooldownExpired, GetStats().AttackCooldown);
	}
}

void ABaseCharacter::PlayAttackMontage()
{
	UAnimMontage* AttackMontage = GetRandomAttackMontage();
	const float Length = AttackMontage->CalculateSequenceLength();

	// Make montage length equal to AttackCooldown, so no matter how slow
	// or fast animation is, it is always the same length
	const float Rate = Length / GetStats().AttackCooldown;
	PlayAnimMontage(AttackMontage, Rate);
}

bool ABaseCharacter::CanMove()
{
	return !IsLockedInAnimation();
}

void ABaseCharacter::MoveTo(const FVector Location)
{
	if (CanMove())
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Location);

		// Stop any montages when start moving
		StopAnimMontage();
	}
}

void ABaseCharacter::StopMoving()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), GetActorLocation());
}

FCharacterStats ABaseCharacter::GetStats() const
{
	return StatsComponent->GetStats();
}

FCharacterStats ABaseCharacter::GetBaseStats() const
{
	return StatsComponent->GetBaseStats();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRotating)
	{
		const FRotator NextRotation = FMath::RInterpConstantTo(GetActorRotation(), RotationState.Target, DeltaTime, RotationState.Speed);
		SetActorRotation(NextRotation);
		if (RotationState.bEndWhenFaceTarget && GetActorRotation().Equals(RotationState.Target, 0.001f))
		{
			StopRotating();
		}
	}
}

void ABaseCharacter::OnAttackCooldownExpired()
{
	bIsAttackInCooldown = false;
}

