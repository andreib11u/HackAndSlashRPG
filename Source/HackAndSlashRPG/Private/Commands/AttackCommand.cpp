// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Commands/AttackCommand.h"
#include "Characters/BaseCharacter.h"

void UAttackCommand::Init(ABaseCharacter* OwnerToSet, ABaseCharacter* TargetToSet)
{
	SetOwner(OwnerToSet);
	Target = TargetToSet;
}

void UAttackCommand::Execute()
{
	OnStartExecute.Broadcast();
	GetOwner()->StartRotating(Target);
	UAnimMontage* AttackMontage = GetOwner()->GetRandomAttackMontage();	
	float Rate = GetOwner()->PlayAnimMontage(AttackMontage);
	GetOwner()->OnAttackLand.AddDynamic(this, &UAttackCommand::OnAttackLand);
}

bool UAttackCommand::CanExecute()
{
	const float TargetDistance = FVector::Distance(GetOwner()->GetActorLocation(), Target->GetActorLocation());
	return TargetDistance < GetOwner()->GetStartingAttackDistance();
}

bool UAttackCommand::CanInterrupt()
{
	return true;
}

void UAttackCommand::EndExecute()
{
	GetOwner()->EndRotating();
	GetOwner()->OnAttackLand.RemoveDynamic(this, &UAttackCommand::OnAttackLand);
	OnEndExecute.Broadcast();
}

void UAttackCommand::OnAttackLand()
{
	// TODO: check for acceptable distance and inflict damage on target
	EndExecute();
}
