// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Navigation/PathFollowingComponent.h"
#include "HackAndSlashPlayerController.generated.h"

class UBasicAttack;
class UAbility;
class UAbilityComponent;
class APlayerCharacter;
class ABaseCharacter;
class UCommandExecutorComponent;
/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API AHackAndSlashPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void SetDestination();

	UFUNCTION(BlueprintCallable)
	void UnsetDestination();
	
	void FindPathFollowingComponent();

	void SetEnemy(ABaseCharacter* EnemyToSet) { Enemy = EnemyToSet; }
	
	UFUNCTION(BlueprintCallable)
	void UnsetEnemy();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	void QueueAttack(ABaseCharacter* EnemyToAttack);
	void UnqueueAttack();


	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAbilityComponent* PlayerAbilityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBasicAttack* AttackAbility;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* ControlledCharacter;

	UPROPERTY(Transient)
	ABaseCharacter* Enemy;

	UPROPERTY(Transient)
	ABaseCharacter* QueuedEnemy;

	bool bIsDestinationSet;
	bool bIsAttackQueued;

	UPROPERTY()
	UPathFollowingComponent* PathFollowingComp;

	UFUNCTION(BlueprintCallable)
	void AbortMove();
};
