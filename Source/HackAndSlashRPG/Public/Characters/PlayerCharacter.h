// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "StatsAndAttributes/Attributes.h"
#include "StatsAndAttributes/Stat.h"
#include "PlayerCharacter.generated.h"

class UPlayerAttribute;
class UAttributes;
class UAttributesComponent;
class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	friend UAttributes;

	APlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PostInitProperties() override;

	UPlayerAttribute* GetAttribute(EAttribute Attribute)const { return Attributes->Attributes[EnumToInt(Attribute)]; }
	UAttributes* GetAttributes()const { return Attributes; }
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* TopDownCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Initial Attributes", meta = (AllowPrivateAccess = "true"))
	int32 InitialStrength = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Initial Attributes", meta = (AllowPrivateAccess = "true"))
	int32 InitialAgility = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Initial Attributes", meta = (AllowPrivateAccess = "true"))
	int32 InitialIntelligence = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Initial Attributes", meta = (AllowPrivateAccess = "true"))
	int32 InitialVitality = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAttributes* Attributes;


};
