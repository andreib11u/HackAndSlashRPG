// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/Inventory/Item/ItemWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Inventory/ItemGrid.h"
#include "Items/Item.h"
#include "UI/CharacterOverview/Inventory/Item/ItemDragDropOperation.h"
#include "UI/CharacterOverview/Inventory/Item/ItemDragWidget.h"

void UItemWidget::Init(UItem* Item)
{
	DisplayingItem = Item;

	ItemImage->SetBrushFromTexture(Item->GetImage());
	ItemBackground->SetBrushColor(GetColorFromRarity(Item->GetRarity()));
}

FLinearColor UItemWidget::GetColorFromRarity(EItemRarity Rarity) const
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

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FKey Key = InMouseEvent.GetEffectingButton();

	// Detect drag on left mouse button
	if (Key == EKeys::LeftMouseButton)
	{
		auto Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return Reply.NativeReply;
	}
	return FReply::Handled();
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	UDragDropOperation* DragDropOp = UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropOperation::StaticClass());
	UItemDragDropOperation* ItemOp = Cast<UItemDragDropOperation>(DragDropOp);

	UItemDragWidget* ItemDragWidget = CreateWidget<UItemDragWidget>(this, *ItemDragWidgetClass);
	ItemDragWidget->Init(DisplayingItem);
	ItemOp->DefaultDragVisual = ItemDragWidget;

	ItemOp->Item = DisplayingItem;

	UItemGrid* ItemGrid = DisplayingItem->GetOwningGrid();
	ItemGrid->StartDraggingItem(DisplayingItem);

	OutOperation = ItemOp;
}
