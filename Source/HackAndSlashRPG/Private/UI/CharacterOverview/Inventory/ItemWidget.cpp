// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/Inventory/ItemWidget.h"
#include "Components/Image.h"
#include "Items/Item.h"

void UItemWidget::Init(UItem* Item)
{
	DisplayingItem = Item;

	ItemImage->SetBrushFromTexture(Item->GetImage());
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetRenderTransformPivot(FVector2D::ZeroVector);
}
