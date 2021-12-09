// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"

#include "BasicAttack.generated.h"

/**
 * Ability for standard attack
 */
UCLASS()
class HACKANDSLASHRPG_API UBasicAttack : public UAbility
{
	GENERATED_BODY()
public:
	UBasicAttack();

	virtual void Execute() override;

	virtual bool CanExecute() override;

	virtual bool CanBeQueued() override;
};
