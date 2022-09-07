// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverviewWidget.generated.h"

class UInventoryWidget;
class UEquipmentWidget;
class UAttributesWidget;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UCharacterOverviewWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(APlayerCharacter* CharacterToDisplay);

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
private:
	UPROPERTY(meta = (BindWidget))
	UAttributesWidget* Attributes;
	UPROPERTY(meta = (BindWidget))
	UEquipmentWidget* Equipment;
	UPROPERTY(meta = (BindWidget))
	UInventoryWidget* Inventory;
};
