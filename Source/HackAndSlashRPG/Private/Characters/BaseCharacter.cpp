// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/BaseCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/AbilityComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
}

void ABaseCharacter::StartRotating(AActor* Target, bool StopWhenFaceTarget)
{
	bIsRotating = true;
	
	const FVector DiffVector = Target->GetActorLocation() - GetActorLocation();
	const FRotator LookAtRotation = FRotator(0.f, DiffVector.Rotation().Yaw, 0.f);
	
	RotationState = FRotationState{ LookAtRotation, StopWhenFaceTarget };
}

void ABaseCharacter::EndRotating()
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
		GetWorld()->GetTimerManager().SetTimer(AttackCooldownTimerHandle,this, &ABaseCharacter::OnAttackCooldownExpired, InternalStats.AttackCooldown);
	}
}

void ABaseCharacter::PlayAttackMontage()
{
	UAnimMontage* AttackMontage = GetRandomAttackMontage();
	const float Length = AttackMontage->CalculateSequenceLength();

	const float Rate = Length / InternalStats.AttackCooldown; // Make montage play as fast as AttackCooldown expires
	
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
	}
}

void ABaseCharacter::StopMoving()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), GetActorLocation());
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
		const FRotator NextRotation = FMath::RInterpConstantTo(GetActorRotation(), RotationState.Target, DeltaTime, 650.f);
		SetActorRotation(NextRotation);
		if (RotationState.bEndWhenFaceTarget && GetActorRotation().Equals(RotationState.Target, 0.001f))
		{
			EndRotating();
		}
	}
}

void ABaseCharacter::OnAttackCooldownExpired()
{
	bIsAttackInCooldown = false;
}

