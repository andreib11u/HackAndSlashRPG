// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/BaseCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/AbilityComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "StatsAndAttributes/Resource.h"
#include "StatsAndAttributes/Stat.h"
#include "StatsAndAttributes/StatCollection.h"

UStat* ABaseCharacter::GetStat(EStat Stat)const
{
	return StatsCollection->Stats[StatToInt(Stat)];
}

float ABaseCharacter::GetStatValue(EStat Stat)const
{
	UStat* FoundStat = StatsCollection->Stats[StatToInt(Stat)];
	return FoundStat->Get();
}

UResource* ABaseCharacter::GetResource(EResource Resource)const
{
	return StatsCollection->Resources[ResourceToInt(Resource)];
}

float ABaseCharacter::GetResourceValue(EResource Resource)const
{
	UResource* FoundResource = StatsCollection->Resources[ResourceToInt(Resource)];
	return FoundResource->Get();
}

void ABaseCharacter::ConfigureStats()
{
	StatsCollection = NewObject<UStatCollection>();
	StatsCollection->Init();

	UStat* ArmorStat = GetStat(EStat::Armor);
	ArmorStat->OnChange.AddDynamic(this, &ABaseCharacter::CalculateDefenseFromArmor);
	CalculateDefenseFromArmor(ArmorStat->Get());

	UStat* AttackSpeedStat = GetStat(EStat::AttackSpeed);
	AttackSpeedStat->OnChange.AddDynamic(this, &ABaseCharacter::CalculateAttackCooldownFromAttackSpeed);
	CalculateAttackCooldownFromAttackSpeed(AttackSpeedStat->Get());

	UStat* MoveSpeedStat = GetStat(EStat::MoveSpeed);
	MoveSpeedStat->OnChange.AddDynamic(this, &ABaseCharacter::OnMoveSpeedChange);
	OnMoveSpeedChange(MoveSpeedStat->Get());

	UStat* HealthRegenStat = GetStat(EStat::HealthRegen);
	HealthRegenStat->OnChange.AddDynamic(this, &ABaseCharacter::OnHealthRegenChange);
	OnHealthRegenChange(HealthRegenStat->Get());

	UStat* ManaRegenStat = GetStat(EStat::ManaRegen);
	ManaRegenStat->OnChange.AddDynamic(this, &ABaseCharacter::OnManaRegenChange);
	OnManaRegenChange(ManaRegenStat->Get());

	StatsCollection->InitResources();
}

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));

}

void ABaseCharacter::PostInitProperties()
{
	Super::PostInitProperties();

	ConfigureStats();
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
		GetWorld()->GetTimerManager().SetTimer(AttackCooldownTimerHandle,this, &ABaseCharacter::OnAttackCooldownExpired, InternalData.AttackCooldown);
	}
}

void ABaseCharacter::PlayAttackMontage()
{
	UAnimMontage* AttackMontage = GetRandomAttackMontage();
	const float Length = AttackMontage->CalculateSequenceLength();

	// Make montage length equal to AttackCooldown, so no matter how slow
	// or fast animation is, it is always the same length
	const float Rate = Length / InternalData.AttackCooldown;
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

void ABaseCharacter::CalculateDefenseFromArmor(float Armor)
{
	InternalData.DefenseMultiplier = 1.f - Armor * 0.01f;
}

void ABaseCharacter::CalculateAttackCooldownFromAttackSpeed(float AttackSpeed)
{
	InternalData.AttackCooldown = 1.f - AttackSpeed * 0.01f;
}

void ABaseCharacter::OnMoveSpeedChange(float MoveSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed * 3.f;
}

void ABaseCharacter::OnHealthRegenChange(float HealthRegen)
{
	InternalData.HealthRegen = HealthRegen;
}

void ABaseCharacter::OnManaRegenChange(float ManaRegen)
{
	InternalData.ManaRegen = ManaRegen;
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

	UResource* HealthRes = GetResource(EResource::Health);
	HealthRes->ChangeValue(InternalData.HealthRegen * DeltaTime);

	UResource* ManaRes = GetResource(EResource::Mana);
	ManaRes->ChangeValue(InternalData.ManaRegen * DeltaTime);
}

void ABaseCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);


}

void ABaseCharacter::OnAttackCooldownExpired()
{
	bIsAttackInCooldown = false;
}

