// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeLabel.generated.h"

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
	void Init(FText Name, int32 CurrentNumber, bool HavePointsToSpend);
	
	UTextBlock* GetAttributeName()const { return AttributeName; }
	UTextBlock* GetAttributeNumber()const { return AttributeNumber; }
	UButton* GetAddAttributeButton()const { return AddAttributeButton; }
	
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttributeName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttributeNumber;
	UPROPERTY(meta = (BindWidget))
	UButton* AddAttributeButton;
};
