// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
private:
	/* Shows when player points mouse cursor on enemy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* TargetDecal;

	UFUNCTION()
	void OnMouseEnter(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnMouseLeft(UPrimitiveComponent* TouchedComponent);

	void SetInitialValues();
	void ConfigureStatCallbacks();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialMaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialMaxMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialMaxDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialMinDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialDamageMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialMoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialAttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialManaRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialHealthRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Values", meta = (AllowPrivateAccess = "true"))
	float InitialMana;


	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentArmor;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentMaxHealth;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentMaxMana;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentMaxDamage;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentMinDamage;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentDamageMultiplier;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentMoveSpeed;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentAttackSpeed;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentManaRegen;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentHealthRegen;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Current Values", meta = (AllowPrivateAccess = "true"))
	float CurrentMana;


	UFUNCTION()
	void SetCurrentArmor(float Armor) { CurrentArmor = Armor; }
	UFUNCTION()
	void SetCurrentMaxHealth(float MaxHealth) { CurrentMaxHealth = MaxHealth; }
	UFUNCTION()
	void SetCurrentMaxMana(float MaxMana) { CurrentMaxMana = MaxMana; }
	UFUNCTION()
	void SetCurrentMaxDamage(float MaxDamage) { CurrentMaxDamage = MaxDamage; }
	UFUNCTION()
	void SetCurrentMinDamage(float MinDamage) { CurrentMinDamage = MinDamage; }
	UFUNCTION()
	void SetCurrentDamageMultiplier(float DamageMultiplyer) { CurrentDamageMultiplier = DamageMultiplyer; }
	UFUNCTION()
	void SetCurrentMoveSpeed(float MoveSpeed) { CurrentMoveSpeed = MoveSpeed; }
	UFUNCTION()
	void SetCurrentAttackSpeed(float AttackSpeed) { CurrentAttackSpeed = AttackSpeed; }
	UFUNCTION()
	void SetCurrentManaRegen(float ManaRegen) { CurrentManaRegen = ManaRegen; }
	UFUNCTION()
	void SetCurrentHealthRegen(float HealthRegen) { CurrentHealthRegen = HealthRegen; }

	UFUNCTION()
	void SetCurrentHealth(float Health) { CurrentHealth = Health; }
	UFUNCTION()
	void SetCurrentMana(float Mana) { CurrentMana = Mana; }

};

