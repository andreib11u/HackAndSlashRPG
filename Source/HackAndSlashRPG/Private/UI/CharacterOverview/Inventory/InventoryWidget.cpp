// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/Inventory/InventoryWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/UniformGridPanel.h"
#include "Inventory/ItemGrid.h"
#include "Items/Item.h"
#include "UI/CharacterOverview/Inventory/Item/ItemDragDropOperation.h"
#include "UI/CharacterOverview/Inventory/Item/ItemHintWidget.h"
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
		ItemWidgets.Add(ItemWidget);
		UCanvasPanelSlot* ItemCanvasSlot = GridCanvas->AddChildToCanvas(ItemWidget);
		ItemCanvasSlot->SetSize(Item->GetSize() * CellSize);
		ItemCanvasSlot->SetPosition(Item->GetGridCoordinates() * CellSize);
	}
}

void UInventoryWidget::RemoveItemWidgets()
{
	for (UItemWidget* ItemWidget : ItemWidgets)
	{
		ItemWidget->RemoveFromParent();
	}
	ItemWidgets.Empty();
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

	DisplayingGrid->OnGridChange.AddDynamic(this, &UInventoryWidget::OnItemGridUpdate);

	Hint = CreateWidget<UItemHintWidget>(this, *ItemHintWidgetClass);
}

bool UInventoryWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                        UDragDropOperation* InOperation)
{
	UItemDragDropOperation* ItemOp = Cast<UItemDragDropOperation>(InOperation);
	if (ItemOp)
	{
		FIntPoint InventoryCoordinates = GetGridCoordinatesFromDraggedItem(InGeometry, InDragDropEvent, ItemOp);

		FIntPoint ItemSize = ItemOp->Item->GetSize();

		if (IsDraggedItemInBorders(InventoryCoordinates, ItemSize))
		{
			if (DisplayingGrid->CanAddItemAt(ItemOp->Item, InventoryCoordinates))
			{
				ShowItemHint(InventoryCoordinates, ItemSize, FLinearColor(0.f, 1.f, 0.f, 0.5f));
			}
			else
			{
				ShowItemHint(InventoryCoordinates, ItemSize, FLinearColor(1.f, 0.f, 0.f, 0.5f));
			}
		}
	}

	return true;
}

void UInventoryWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	RemoveHint();
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	RemoveHint();

	UItemDragDropOperation* ItemOp = Cast<UItemDragDropOperation>(InOperation);
	if (ItemOp)
	{
		FIntPoint Coordinates = GetGridCoordinatesFromDraggedItem(InGeometry, InDragDropEvent, ItemOp);
		if (DisplayingGrid->CanAddItemAt(ItemOp->Item, Coordinates))
		{
			if (ItemOp->Item->GetOwningGrid() == DisplayingGrid)
			{
				DisplayingGrid->MoveDraggingItemInSameGrid(Coordinates);
			}
		}
		else
		{
			ItemOp->Item->GetOwningGrid()->CancelDraggingItem();
		}
	}

	return true;
}

void UInventoryWidget::RemoveHint()
{
	Hint->RemoveFromParent();
}

FIntPoint UInventoryWidget::GetGridCoordinatesFromDraggedItem(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UItemDragDropOperation* ItemDragDropOp)
{
	// Cursor position local to this widget
	FVector2D LocalCursorPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());

	FVector2D ItemSize = { ItemDragDropOp->Item->GetSize().X * UItemWidget::GetCellSize(),
							ItemDragDropOp->Item->GetSize().Y * UItemWidget::GetCellSize() };

	FVector2D DragOffset = ItemSize * 0.5f;

	float HalfCell = UItemWidget::GetCellSize() / 2.f;

	return LocalToGrid(LocalCursorPosition - DragOffset + HalfCell);
}

FIntPoint UInventoryWidget::LocalToGrid(FVector2D LocalPosition)
{
	FIntPoint Result;

	Result.X = LocalPosition.X / UItemWidget::GetCellSize();
	Result.Y = LocalPosition.Y / UItemWidget::GetCellSize();
	return Result;
}

bool UInventoryWidget::IsDraggedItemInBorders(FIntPoint GridCoordinates, FIntPoint ItemSize)
{
	return GridCoordinates.X >= 0 && GridCoordinates.Y >= 0 &&
		GridCoordinates.X + ItemSize.X <= DisplayingGrid->GetSize().X &&
		GridCoordinates.Y + ItemSize.Y <= DisplayingGrid->GetSize().Y;
}

void UInventoryWidget::ShowItemHint(FIntPoint Coordinates, FIntPoint ItemSize, FLinearColor Color)
{
	Hint->SetColorAndOpacity(Color);
	UCanvasPanelSlot* HintSlot = GridCanvas->AddChildToCanvas(Hint);
	HintSlot->SetSize(FVector2D(ItemSize.X * UItemWidget::GetCellSize(), ItemSize.Y * UItemWidget::GetCellSize()));
	HintSlot->SetPosition(FVector2D(Coordinates.X * UItemWidget::GetCellSize(), Coordinates.Y * UItemWidget::GetCellSize()));
}

void UInventoryWidget::OnItemGridUpdate()
{
	RemoveItemWidgets();
	CreateItemWidgets(DisplayingGrid->GetItems());
}
