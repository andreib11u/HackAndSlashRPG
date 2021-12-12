// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

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
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PostInitProperties() override;

	struct FAttributes GetAttributes()const;
	
protected:
	
private:
	UFUNCTION()
	void OnStrengthChange(int32 Change);
	UFUNCTION()
	void OnAgilityChange(int32 Change);
	UFUNCTION()
	void OnIntelligenceChange(int32 Change);
	UFUNCTION()
	void OnVitalityChange(int32 Change);

	void ConfigureAttributeComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	UAttributesComponent* AttributesComponent;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* TopDownCamera;
};
