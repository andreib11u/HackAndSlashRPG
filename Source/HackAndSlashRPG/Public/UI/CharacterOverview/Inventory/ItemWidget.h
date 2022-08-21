// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UBorder;
class UImage;
class UItem;
/**
 * Displays item. Allows drag and drop
 */
UCLASS()
class HACKANDSLASHRPG_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(UItem* Item);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))
	UBorder* ItemBackground;

	UPROPERTY()
	UItem* DisplayingItem;
};
