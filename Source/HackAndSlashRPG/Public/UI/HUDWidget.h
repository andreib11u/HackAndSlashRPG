// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class APlayerCharacter;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class HACKANDSLASHRPG_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetCharacterToDisplay(APlayerCharacter* PlayerCharacter);
	
private:
	UFUNCTION()
	void OnHealthChange(const float CurrentHealth, const float MaxHealth);
	UFUNCTION()
	void OnManaChange(const float CurrentMana, const float MaxMana);
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ManaBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ExpBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ManaText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelText;
};
