// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/Inventory/Item/ItemHintWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "UI/CharacterOverview/Inventory/Item/ItemWidget.h"

void UItemHintWidget::SetSize(FIntPoint ItemSize)
{
	ItemSizeBox->SetHeightOverride(ItemSize.Y * UItemWidget::GetCellSize());
	ItemSizeBox->SetWidthOverride(ItemSize.X * UItemWidget::GetCellSize());
}

void UItemHintWidget::SetColor(FLinearColor Color)
{
	HintImage->SetColorAndOpacity(Color);
}

void UItemHintWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetRenderTransformPivot(FVector2D::ZeroVector);
}
