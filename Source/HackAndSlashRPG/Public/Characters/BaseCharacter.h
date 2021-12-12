// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"

#include "Components/AbilityComponent.h"
#include "Components/StatsComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UStatsComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRotationEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackLand);

/** Info required for rotation */
struct FRotationState
{
	FRotator Target;
	bool bEndWhenFaceTarget;
	float Speed;
};

/**
 * Base rpg character
 */
UCLASS(Abstract)
class HACKANDSLASHRPG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for character's properties
	ABaseCharacter();

	UAnimMontage* GetRandomAttackMontage() const { return AttackMontages[FMath::RandRange(0, AttackMontages.Num() - 1)]; }

	bool IsLockedInAnimation()const { return bLockedInAnimation; }

	/**
	 * Rotate to face Target
	 * @param Target - Location to face
	 * @param RotationSpeed 
	 * @param StopWhenFaceTarget - If true - stops rotating when faced target,
	 * otherwise need to call StopRotating() to stop always looking at target
	 */
	UFUNCTION(BlueprintCallable)
	void StartRotating(const FVector Target, const float RotationSpeed = 650.f, bool StopWhenFaceTarget = true);

	UFUNCTION(BlueprintCallable)
	void StopRotating();

	UFUNCTION(BlueprintCallable)
	void StartAttackCooldown();

	UFUNCTION(BlueprintCallable)
	bool IsAttackInCooldown()const { return bIsAttackInCooldown; }

	void SetLockedInAnimation(bool bIsLockedInAnimation) { bLockedInAnimation = bIsLockedInAnimation; }

	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	bool CanMove();
	
	UFUNCTION(BlueprintCallable)
	void MoveTo(const FVector Location);

	UFUNCTION(BlueprintCallable)
	void StopMoving();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnRotationEnd OnRotationEnd;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAttackLand OnAttackLand;

	UFUNCTION(BlueprintCallable)
	FCharacterStats GetStats()const;

	UFUNCTION(BlueprintCallable)
	FCharacterStats GetBaseStats()const;

	UStatsComponent* GetStatsComponent()const { return StatsComponent; }
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStatsComponent* StatsComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAbilityComponent* AbilityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	bool bIsRotating;
	
	FRotationState RotationState;

	FTimerHandle AttackCooldownTimerHandle;

	UFUNCTION()
	void OnAttackCooldownExpired();
	
	/** Cannot start an attack when the attack is in cooldown */
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bIsAttackInCooldown;
	
	/** Cannot start other actions when locked in an animation */
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Montages", meta = (AllowPrivateAccess = "true"))
	bool bLockedInAnimation;
};
