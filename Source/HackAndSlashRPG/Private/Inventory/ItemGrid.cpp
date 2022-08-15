// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "Inventory/ItemGrid.h"

#include "Items/Item.h"


void UItemGrid::AllocateCells()
{
	Cells.Reserve(Size.X * Size.Y);

	for (int32 WidthCount = 0; WidthCount < Size.X; ++WidthCount)
	{
		for (int32 HeightCount = 0; HeightCount < Size.Y; ++HeightCount)
		{
			Cells.Add(EMPTY_CELL);
		}
	}
}

UItemGrid* UItemGrid::Create(FIntPoint GridSize)
{
	UItemGrid* NewGrid = NewObject<UItemGrid>();
	NewGrid->Size = GridSize;

	NewGrid->AllocateCells();

	return NewGrid;
}

void UItemGrid::AddItemAndBroadcast(UItem* Item, FIntPoint Coordinates)
{
	AddItemInternal(Item, Coordinates);
	OnGridChange.Broadcast();
	OnItemAdded.Broadcast(Item);
}

bool UItemGrid::AddItem(UItem* Item)
{
	FIntPoint FoundCoordinates = FindEmptyAreaCoordinates(Item->GetSize());
	if (FoundCoordinates != FIntPoint::NoneValue)
	{
		AddItemAndBroadcast(Item, FoundCoordinates);
		return true;
	}
	return false;
}

bool UItemGrid::AddManyItems(TArray<UItem*> InItems, TArray<UItem*>& OutNotAddedItems)
{
	bool bAnyItemAdded = false;
	bool bAllItemsAdded = true;
	TArray<UItem*> NotAddedItems;

	for (UItem* Item : InItems)
	{
		FIntPoint EmptyArea = FindEmptyAreaCoordinates(Item->GetSize());
		if (EmptyArea != FIntPoint::NoneValue)
		{
			AddItemInternal(Item, EmptyArea);
			OnItemAdded.Broadcast(Item);
			NotAddedItems.Add(Item);
			bAnyItemAdded = true;
		}
		else
		{
			bAllItemsAdded = false;
		}
	}

	if (bAnyItemAdded)
	{
		OnGridChange.Broadcast();
		OutNotAddedItems = NotAddedItems;
	}

	return bAllItemsAdded;
}

bool UItemGrid::AddItemAt(UItem* Item, FIntPoint Coordinates)
{
	if (IsAreaEmpty(Coordinates, Item->GetSize()))
	{
		AddItemAndBroadcast(Item, Coordinates);
		return true;
	}
	return false;
}

void UItemGrid::RemoveItemAndBroadcast(UItem* Item)
{
	RemoveItemInternal(Item);
	OnItemRemoved.Broadcast(Item);
	OnGridChange.Broadcast();
}

void UItemGrid::RemoveItem(UItem* Item)
{
	if (Items.Contains(Item))
	{
		RemoveItemAndBroadcast(Item);
	}
}

void UItemGrid::SetCell(FIntPoint Coordinates, uint32 Id)
{
	Cells[GetIndex(Coordinates)] = Id;
}

void UItemGrid::FillArea(FIntPoint TopLeftPoint, FIntPoint AreaSize, uint32 Id)
{
	for (int32 WidthCount = 0; WidthCount < AreaSize.X; ++WidthCount)
	{
		for (int32 HeightCount = 0; HeightCount < AreaSize.Y; ++HeightCount)
		{
			SetCell(FIntPoint(TopLeftPoint.X + WidthCount, TopLeftPoint.Y + HeightCount), Id);
		}
	}
}

FIntPoint UItemGrid::FindEmptyAreaCoordinates(FIntPoint ItemSize)
{
	FIntPoint Result = FIntPoint::NoneValue;

	if (ItemSize.Y > Size.Y || ItemSize.X > Size.X)
		return Result;

	for (int32 HeightCount = 0; HeightCount <= Size.Y - ItemSize.Y; ++HeightCount)
	{
		for (int32 WidthHeight = 0; WidthHeight <= Size.X - ItemSize.X; ++WidthHeight)
		{
			if (IsAreaEmpty(FIntPoint(WidthHeight, HeightCount), ItemSize))
			{
				Result = FIntPoint(WidthHeight, HeightCount);
				return Result;
			}
		}
	}

	return Result;
}

bool UItemGrid::IsAreaEmpty(FIntPoint GridCoordinates, FIntPoint ItemSize) const
{
	bool bResult = true;

	if (GridCoordinates.X + ItemSize.X > Size.X || GridCoordinates.Y + ItemSize.Y > Size.Y)
		return false;

	for (int32 WidthCount = 0; WidthCount < ItemSize.X; ++WidthCount)
	{
		for (int32 HeightCount = 0; HeightCount < ItemSize.Y; ++HeightCount)
		{
			uint32 Cell = GetCell(FIntPoint(GridCoordinates.X + WidthCount, GridCoordinates.Y + HeightCount));
			if (Cell != EMPTY_CELL)
			{
				return false;
			}
		}
	}

	return bResult;
}


void UItemGrid::AddItemInternal(UItem* Item, FIntPoint Coordinates)
{
	Items.Add(Item);
	Item->SetGridCoordinates(Coordinates);
	FillArea(Coordinates, Item->GetSize(), Item->GetUniqueID());
}

void UItemGrid::RemoveItemInternal(UItem* Item)
{
	Items.Remove(Item);
	Item->SetGridCoordinates(FIntPoint::NoneValue);
	FillArea(Item->GetGridCoordinates(), Item->GetSize(), EMPTY_CELL);
}
