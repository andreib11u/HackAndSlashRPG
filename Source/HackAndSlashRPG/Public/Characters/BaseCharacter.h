// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"

#include "Components/AbilityComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

enum class EResource : uint8;
enum class EStat : uint8;
class UResource;
class UStat;
class UStatCollection;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRotationEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackLand);

/** Info required for rotation */
struct FRotationState
{
	FRotator Target;
	bool bEndWhenFaceTarget;
	float Speed;
};


struct FInternalData
{
	/** All incoming damage multiplies on this */
	float DefenseMultiplier;

	float AttackCooldown;

	float HealthRegen;

	float ManaRegen;
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

	virtual void PostInitProperties() override;

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
	
	bool IsLockedInAnimation()const { return bLockedInAnimation; }
	void SetLockedInAnimation(bool bIsLockedInAnimation) { bLockedInAnimation = bIsLockedInAnimation; }

	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	bool CanMove();
	
	UFUNCTION(BlueprintCallable)
	void MoveTo(const FVector Location);

	UFUNCTION(BlueprintCallable)
	void StopMoving();

	// Changing stats callbacks
	
	UFUNCTION()
	void CalculateDefenseFromArmor(float Armor);

	UFUNCTION()
	void CalculateAttackCooldownFromAttackSpeed(float AttackSpeed);

	UFUNCTION()
	void OnMoveSpeedChange(float MoveSpeed);

	UFUNCTION()
	void OnHealthRegenChange(float HealthRegen);
	
	UFUNCTION()
	void OnManaRegenChange(float ManaRegen);

	// Delegates
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnRotationEnd OnRotationEnd;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAttackLand OnAttackLand;

	/** Getters */

	UAnimMontage* GetRandomAttackMontage() const { return AttackMontages[FMath::RandRange(0, AttackMontages.Num() - 1)]; }
	UStatCollection* GetStats()const { return StatsCollection; }
	inline UStat* GetStat(EStat Stat)const;
	inline float GetStatValue(EStat Stat)const;
	inline UResource* GetResource(EResource Resource)const;
	inline float GetResourceValue(EResource Resource)const;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	void ConfigureStats();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStatCollection* StatsCollection;

	FInternalData InternalData;
	
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
