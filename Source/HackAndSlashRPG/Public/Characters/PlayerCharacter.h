// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FAttributes
{
	GENERATED_BODY()

	int32 Strength = 10;
	int32 Agility = 10;
	int32 Intelligence = 10;
	int32 Vitality = 10;

	int32 HpPerVitality = 11;
	int32 MpPerIntelligence = 3;
	float DmgPerStrength = 0.8f;
	float CooldownReductionPerAgility = 0.01f;
};

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PostInitProperties() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowProtectedAccess = "true"))
	FAttributes Attributes;
private:
	void ApplyAttributes();
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* TopDownCamera;
};
