// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Commands/Command.h"
#include "AttackCommand.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UAttackCommand : public UCommand
{
	GENERATED_BODY()
public:
	void Init(ABaseCharacter* OwnerToSet, ABaseCharacter* TargetToSet);
	virtual void Execute() override;
	virtual bool CanExecute() override;
	virtual bool CanInterrupt() override;
	virtual void EndExecute() override;
private:
	UPROPERTY()
	ABaseCharacter* Target;
	
	UFUNCTION()
	void OnAttackLand();
	FDelegateHandle AttackLandHandle;
};
