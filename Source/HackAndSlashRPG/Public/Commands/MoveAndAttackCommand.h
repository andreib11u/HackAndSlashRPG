// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Commands/MoveCommand.h"
#include "MoveAndAttackCommand.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UMoveAndAttackCommand : public UMoveCommand
{
	GENERATED_BODY()
public:
	void Init(ABaseCharacter* OwnerToSet, ABaseCharacter* TargetToSet);
	virtual void Execute() override;
	void Attack(ABaseCharacter* AttackTarget);
	virtual void OnPathComplete(FAIRequestID RequestID, const FPathFollowingResult& PathFollowingResult) override;
private:
	UPROPERTY()
	ABaseCharacter* Target;
};
