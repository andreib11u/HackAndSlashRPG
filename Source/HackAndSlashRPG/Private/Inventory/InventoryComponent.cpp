// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "Inventory/InventoryComponent.h"

#include "Inventory/ItemGrid.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

bool UInventoryComponent::AddItem(UItem* Item)
{
	for (UItemGrid* Grid : Grids)
	{
		if (Grid->AddItem(Item))
		{
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::AddManyItems(TArray<UItem*> Items, TArray<UItem*>& OutNotAddedItems)
{
	TArray<UItem*> ItemsToAdd = Items;
	TArray<UItem*> NotAddedItems;
	for (UItemGrid* Grid : Grids)
	{
		Grid->AddManyItems(ItemsToAdd, NotAddedItems);
		if (NotAddedItems.Num() == 0)
		{
			return true;
		}
		ItemsToAdd = NotAddedItems;
	}
	OutNotAddedItems = NotAddedItems;

	if (NotAddedItems.Num() != 0)
	{
		return false;
	}
	return true;
}


void UInventoryComponent::RemoveItem(UItem* Item)
{
	for (UItemGrid* Grid : Grids)
	{
		if (Grid->GetItems().Contains(Item))
		{
			Grid->RemoveItem(Item);
			return;
		}
	}
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	AddDefaultGrid();
	AddDefaultItems();
}

void UInventoryComponent::PostInitProperties()
{
	Super::PostInitProperties();
	
}

void UInventoryComponent::AddDefaultGrid()
{
	UItemGrid* DefaultItemGrid = UItemGrid::Create(DefaultGridSize);
	Grids.Empty();
	Grids.Add(DefaultItemGrid);
}

void UInventoryComponent::AddDefaultItems()
{
	TArray<UItem*> NotAddedItems;
	AddManyItems(DefaultItems, NotAddedItems);
}

