// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"

#include "Components/AbilityComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRotationEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackLand);

class UCommandExecutorComponent;

struct FRotationState
{
	FRotator Target;
	bool bEndWhenFaceTarget;
};

USTRUCT(BlueprintType)
struct FInternalStats
{
	GENERATED_BODY()

	int32 Health;
	int32 MaxHealth = 100;
	
	int32 Mana;
	int32 MaxMana = 30;

	float AttackCooldown = 1.f;
	float MinAttackCooldown = 0.25f;

	float Damage = 10.f;
	
	float DamageMultiplier = 1.f;
	float MinDamageMultiplier = 0.1f;

	float DefenseMultiplier = 0.f;
	float MinDefenseMultiplier = 0.f;
	float MaxDefenseMultiplier = 0.85f;

	FInternalStats()
	{
		Health = MaxHealth;
		Mana = MaxMana;
	}

	static FInternalStats GetDefaultStats()
	{
		static FInternalStats DefaultStats = FInternalStats();
		return DefaultStats;
	}
};

/**
 * Base rpg character
 */
UCLASS(Abstract)
class HACKANDSLASHRPG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	/** Attack can be started at this distance */
	float GetStartingAttackDistance()const { return MaxAttackDistance; }
	
	/** When attack lands target must be in this range */
	float GetMaxReachAttackDistance()const { return MaxAttackDistance * 2.f; }

	UAnimMontage* GetRandomAttackMontage() const { return AttackMontages[FMath::RandRange(0, AttackMontages.Num() - 1)]; }

	bool IsLockedInAnimation()const { return bLockedInAnimation; }

	UFUNCTION(BlueprintCallable)
	void StartRotating(AActor* Target, bool StopWhenFaceTarget = true);

	UFUNCTION(BlueprintCallable)
	void EndRotating();

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

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowProtectedAccess = "true"))
	FInternalStats InternalStats;
private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAbilityComponent* AbilityComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonStats", meta = (AllowPrivateAccess = "true"))
	float MaxAttackDistance = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(VisibleAnywhere, Transient, Category="Rotation", meta = (AllowPrivateAccess = "true"))
	bool bIsRotating;

	FRotationState RotationState;

	FTimerHandle AttackCooldownTimerHandle;

	UFUNCTION()
	void OnAttackCooldownExpired();
	
	/** Cannot start an attack when attack is in cooldown */
	UPROPERTY(BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bIsAttackInCooldown;
	
	/** Cannot start other actions when locked in animation */
	UPROPERTY(BlueprintReadWrite, Category = "Montages", meta = (AllowPrivateAccess = "true"))
	bool bLockedInAnimation;
};
