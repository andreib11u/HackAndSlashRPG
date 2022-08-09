// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeLabel.generated.h"

class UPlayerAttribute;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UAttributeLabel : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(UPlayerAttribute* AttributeToDisplay);

	UFUNCTION()
	void OnPointsChange(int32 Points);
	
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttributeName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttributeNumber;
	UPROPERTY(meta = (BindWidget))
	UButton* AddAttributeButton;
};
