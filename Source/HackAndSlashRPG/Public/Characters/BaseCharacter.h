// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION(BlueprintCallable)
	void StartRotating(AActor* Target, bool StopWhenFaceTarget = true);

	UFUNCTION(BlueprintCallable)
	void EndRotating();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnRotationEnd OnRotationEnd;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAttackLand OnAttackLand;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UCommandExecutorComponent* GetCommandExecutorComponent()const { return CommandExecutor; }
	

private:
	UPROPERTY(VisibleAnywhere)
	UCommandExecutorComponent* CommandExecutor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonStats", meta = (AllowPrivateAccess = "true"))
	float MaxAttackDistance = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(VisibleAnywhere, Transient, Category="Rotation", meta = (AllowPrivateAccess = "true"))
	bool bIsRotating;

	FRotationState RotationState;
};
