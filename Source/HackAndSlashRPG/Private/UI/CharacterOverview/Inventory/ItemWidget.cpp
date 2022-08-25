// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/Inventory/ItemWidget.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Items/Item.h"

void UItemWidget::Init(UItem* Item)
{
	DisplayingItem = Item;

	ItemImage->SetBrushFromTexture(Item->GetImage());
	ItemBackground->SetBrushColor(GetColorFromRarity(Item->GetRarity()));
}

FLinearColor UItemWidget::GetColorFromRarity(EItemRarity Rarity)
{
	switch (Rarity)
	{
	case EItemRarity::Common: 
		return Common;
	case EItemRarity::Uncommon: 
		return Uncommon;
	case EItemRarity::Rare: 
		return Rare;
	case EItemRarity::Legendary: 
		return Legendary;
	default: 
		checkNoEntry();
	}
	return FLinearColor::Red;
}


void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetRenderTransformPivot(FVector2D::ZeroVector);
}
