// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributesWidget.generated.h"

class UAttributes;
class UAttributesComponent;
class UAttributeLabel;
/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UAttributesWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(UAttributes* AttributesToDisplay);
private:
	UPROPERTY(meta = (BindWidget))
	UAttributeLabel* StrengthAttributeLabel;
	UPROPERTY(meta = (BindWidget))
	UAttributeLabel* AgilityAttributeLabel;
	UPROPERTY(meta = (BindWidget))
	UAttributeLabel* IntelligenceAttributeLabel;
	UPROPERTY(meta = (BindWidget))
	UAttributeLabel* VitalityAttributeLabel;
};
