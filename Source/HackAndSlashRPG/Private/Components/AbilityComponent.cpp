// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Components/AbilityComponent.h"
#include "Abilities/Ability.h"
#include "Characters/BaseCharacter.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAbilityComponent::ExecuteAbility(UAbility* Ability)
{
	if (Ability->HasAcceptableDistance())
	{
		if (Ability->CanExecute())
		{
			Ability->Execute();
		}
	}
	else if (Ability->DoesRunToTarget() && !Ability->HasAcceptableDistance())
	{
		if (Ability->CanBeQueued())
		{
			QueueAbility(Ability);
		}
	}
	else
	{
		// do nothing
	}
}

void UAbilityComponent::QueueAbility(UAbility* Ability)
{
	CurrentAbility = Ability;
	CurrentAbility->RunToTarget();
	bQueuedAbility = true;
}

void UAbilityComponent::UnQueueCurrentAbility()
{
	CurrentAbility = nullptr;
	bQueuedAbility = false;
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bQueuedAbility && CurrentAbility->HasAcceptableDistance())
	{
		if (CurrentAbility->CanExecute())
		{
			CurrentAbility->Execute();
		}

		UnQueueCurrentAbility();
	}
}

