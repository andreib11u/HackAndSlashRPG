// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAbility, Log, All);

class ABaseCharacter;
/**
 * Base class for abilities
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class HACKANDSLASHRPG_API UAbility : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Execute();

	UFUNCTION(BlueprintCallable)
	virtual bool CanExecute();

	UFUNCTION(BlueprintCallable)
	virtual bool CanBeQueued();

	UFUNCTION(BlueprintCallable)
	float DistanceToTarget()const;

	UFUNCTION(BlueprintCallable)
	bool HasAcceptableDistance()const;

	UFUNCTION(BlueprintCallable)
	void RunToTarget();

	UFUNCTION(BlueprintCallable)
	void StopMoving();
	
	void SetOwner(ABaseCharacter* OwnerToSet) { Owner = OwnerToSet; }

	/** Set either character or location, but not both */
	void SetTargetCharacter(ABaseCharacter* Target) { TargetCharacter = Target; }	
	/** Set either character or location, but not both */
	void SetTargetLocation(const FVector Target) { TargetLocation = Target; }

	bool DoesRunToTarget()const { return bRunToTarget; }
protected:
	
	
	UPROPERTY(BlueprintReadWrite, Category = "Target", meta = (AllowProtectedAccess = "true"))
	ABaseCharacter* TargetCharacter;
	UPROPERTY(BlueprintReadWrite, Category = "Target", meta = (AllowProtectedAccess = "true"))
	FVector TargetLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Owner", meta = (AllowProtectedAccess = "true"))
	ABaseCharacter* Owner;
	
	/** Minimal distance between a target and an owner for the ability to be used */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (AllowProtectedAccess = "true"))
	float MinRange;

	/** When the distance between a target and an owner is less than MinRange,
	 *owner runs closer when this is true, otherwise doesn't do anything. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (AllowProtectedAccess = "true"))
	bool bRunToTarget;
};
