// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Abilities/BasicAttack.h"
#include "Characters/BaseCharacter.h"

UBasicAttack::UBasicAttack()
{
	bRunToTarget = true;
	MinRange = 120.f;
}

void UBasicAttack::Execute()
{
	Owner->StartRotating(TargetCharacter);
	
	Owner->SetLockedInAnimation(true); // Unlock happens in AnimNotify when the attack "lands" on an enemy
	
	Owner->StopMoving();

	Owner->StartAttackCooldown();

	Owner->PlayAttackMontage();
}

bool UBasicAttack::CanExecute()
{
	if (!TargetCharacter)
	{
		UE_LOG(LogAbility, Error, TEXT("TargetCharacter of UBasicAttack ability is invalid"))
		return false;
	}

	if (Owner->IsAttackInCooldown())
	{
		return false;
	}
	
	return true;
}

bool UBasicAttack::CanBeQueued()
{
	if (Owner->IsLockedInAnimation())
	{
		return false;
	}

	return true;
}
