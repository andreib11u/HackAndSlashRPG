// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/Inventory/InventoryWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/UniformGridPanel.h"
#include "Inventory/ItemGrid.h"
#include "Items/Item.h"
#include "UI/CharacterOverview/Inventory/Item/ItemWidget.h"

void UInventoryWidget::CreateGrid(FIntPoint Size)
{
	for (int ColumnCount = 0; ColumnCount < Size.X; ++ColumnCount)
	{
		for (int RowCount = 0; RowCount < Size.Y; ++RowCount)
		{
			UUserWidget* CellWidget = CreateWidget(this, *CellWidgetClass);
			VisualGrid->AddChildToUniformGrid(CellWidget, RowCount, ColumnCount);
		}
	}
}

void UInventoryWidget::CreateItemWidgets(const TArray<UItem*>& Items)
{
	for (UItem* Item : Items)
	{
		UItemWidget* ItemWidget = CreateWidget<UItemWidget>(this, *ItemWidgetClass);
		ItemWidget->Init(Item);
		UCanvasPanelSlot* ItemCanvasSlot = GridCanvas->AddChildToCanvas(ItemWidget);
		ItemCanvasSlot->SetSize(Item->GetSize() * CellSize);
		ItemCanvasSlot->SetPosition(Item->GetGridCoordinates() * CellSize);
	}
}

void UInventoryWidget::Init(UItemGrid* ItemGrid)
{
	check(ItemGrid);
	DisplayingGrid = ItemGrid;

	FIntPoint Size = DisplayingGrid->GetSize();

	GridSize->SetWidthOverride(Size.X * CellSize);
	GridSize->SetHeightOverride(Size.Y * CellSize);

	CreateGrid(Size);

	CreateItemWidgets(ItemGrid->GetItems());
}

void UInventoryWidget::OnItemGridUpdate()
{

}
