// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

enum class EItemRarity : uint8;
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

	FLinearColor GetColorFromRarity(EItemRarity Rarity);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))
	UBorder* ItemBackground;

	UPROPERTY()
	UItem* DisplayingItem;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FLinearColor Common;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FLinearColor Uncommon;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FLinearColor Rare;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FLinearColor Legendary;
};
