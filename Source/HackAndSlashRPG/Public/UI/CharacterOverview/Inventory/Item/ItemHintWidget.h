// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemHintWidget.generated.h"

class UImage;
class USizeBox;
/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UItemHintWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetSize(FIntPoint ItemSize);
	void SetColor(FLinearColor Color);

protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta = (BindWidget))
	UImage* HintImage;
	UPROPERTY(meta = (BindWidget))
	USizeBox* ItemSizeBox;
};
