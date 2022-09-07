// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/CharacterOverviewWidget.h"

#include "Characters/PlayerCharacter.h"
#include "Inventory/InventoryComponent.h"
#include "UI/CharacterOverview/AttributesWidget.h"
#include "UI/CharacterOverview/Inventory/InventoryWidget.h"

void UCharacterOverviewWidget::Init(APlayerCharacter* CharacterToDisplay)
{
	Attributes->Init(CharacterToDisplay->GetAttributes());

	UInventoryComponent* PlayerInventory = CharacterToDisplay->FindComponentByClass<UInventoryComponent>();
	Inventory->Init(PlayerInventory->GetDefaultGrid());
}

FReply UCharacterOverviewWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

