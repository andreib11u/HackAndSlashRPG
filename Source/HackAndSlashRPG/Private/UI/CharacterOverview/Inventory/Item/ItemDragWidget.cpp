// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/Inventory/Item/ItemDragWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Items/Item.h"
#include "UI/CharacterOverview/Inventory/Item/ItemWidget.h"

void UItemDragWidget::Init(UItem* DraggedItem)
{
	if (DraggedItem)
	{
		const float CellSize = UItemWidget::GetCellSize();

		ItemSizeBox->SetWidthOverride(DraggedItem->GetSize().X * CellSize);
		ItemSizeBox->SetHeightOverride(DraggedItem->GetSize().Y * CellSize);
		ItemImage->SetBrushFromTexture(DraggedItem->GetImage());
		ItemImage->SetOpacity(0.5);
	}
}
