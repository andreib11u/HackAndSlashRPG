// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemGrid.generated.h"

#define EMPTY_CELL 0

class UItem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, UItem*, AddedItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, UItem*, RemovedItem);

/**
 * Grid space that can contain UItems. Implemented as an array of items
 * and array of cells
 */
UCLASS()
class HACKANDSLASHRPG_API UItemGrid : public UObject
{
	GENERATED_BODY()
public:
	static UItemGrid* Create(FIntPoint GridSize);

	/**
	 * Add an item at first free location 
	 * @param Item - item to add
	 * @return false if there is no free locations
	 */
	bool AddItem(UItem* Item);

	/**
	 * Add an item at specific location
	 * @param Item - item to add
	 * @param Coordinates - location
	 * @return false if item doesn't fit in given coordinates
	 */
	bool AddItemAt(UItem* Item, FIntPoint Coordinates);

	/**
	 * Remove item from the grid if there is one
	 * @param Item - item to remove
	 */
	void RemoveItem(UItem* Item);

	/**
	 * Set particular cell in a grid with Id
	 * @param Coordinates - place where to set Id
	 * @param Id - Id to set
	 */
	void SetCell(FIntPoint Coordinates, uint32 Id);

	/** Fill area in grid with given Id */
	void FillArea(FIntPoint TopLeftPoint, FIntPoint AreaSize, uint32 Id);

	/** @return grid coordinates or FIntPoint::NoneValue if empty area isn't found	*/
	FIntPoint FindEmptyAreaCoordinates(FIntPoint ItemSize);

	/**
	 * true if there is no other items or borders in given area
	 * @param GridCoordinates - Top left point of an item in inventory grid
	 * @param ItemSize - how many cells to check for an item to fit
	 * */
	bool IsAreaEmpty(FIntPoint GridCoordinates, FIntPoint ItemSize) const;

	UPROPERTY(BlueprintAssignable)
	FOnGridChange OnGridChange;

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	TArray<UItem*> GetItems()const { return Items; }

private:
	/** functions for working with one-dimensional array as with two-dimensional and otherwise */

	uint32 GetCell(FIntPoint Coordinates)const { return Cells[GetIndex(Coordinates)]; }
	int32 GetIndex(FIntPoint Coordinates)const { return Coordinates.Y * Size.X + Coordinates.X; }
	int32 GetColumn(int32 Index)const { return Index % Size.X; }
	int32 GetRow(int32 Index)const { return Index / Size.X; }

	void AllocateCells();

	void AddItemAndBroadcast(UItem* Item, FIntPoint Coordinates);

	void AddItemInternal(UItem* Item, FIntPoint Coordinates);
	void RemoveItemInternal(UItem* Item);

	UPROPERTY(VisibleAnywhere)
	FIntPoint Size;

	UPROPERTY(VisibleAnywhere)
	TArray<UItem*> Items;

	UPROPERTY(VisibleAnywhere)
	TArray<uint32> Cells;
};
