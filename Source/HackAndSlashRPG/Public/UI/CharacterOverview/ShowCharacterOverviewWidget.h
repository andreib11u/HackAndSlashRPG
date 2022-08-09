// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowCharacterOverviewWidget.generated.h"

class APlayerCharacter;
class UCharacterOverviewWidget;
/**
 * Animated widget that shows CharacterOverviewWidget
 */
UCLASS()
class HACKANDSLASHRPG_API UShowCharacterOverviewWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(APlayerCharacter* CharacterToDisplay);

	UFUNCTION(BlueprintCallable)
	void Close();

	float GetShowWidgetAnimTime()const { return AnimTime; }
private:
	UPROPERTY(meta = (BindWidget))
	UCharacterOverviewWidget* WidgetToShow;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowWidget;
	float AnimTime = 0.5f;

	FWidgetAnimationDynamicEvent OnWidgetAnimationChanged;

	UFUNCTION()
	void OnShowWidgetAnimationEnd();
};
