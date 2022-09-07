// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemGrid.generated.h"

enum { EMPTY_CELL = 0 };

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
	 * Asks if item can be added at certain coordinates
	 * @param Item - item to add
	 * @param Coordinates - coordinates to add item to
	 * @return whether grid can place the item or not
	 */
	bool CanAddItemAt(UItem* Item, FIntPoint Coordinates);

	/**
	 * Asks if there is a place for an item in the grid
	 * @param Item - item to add
	 * @return true if place is found
	 * @note probably don't need this function
	 */
	bool CanAddItem(UItem* Item);

	/**
	 * Adds an array of items
	 * @param InItems - Items to add
	 * @param OutNotAddedItems - return items that are not added
	 * @return - true if every item added
	 */
	bool AddManyItems(TArray<UItem*> InItems, TArray<UItem*>& OutNotAddedItems);

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

	/** Called when item drag detected. Removes item from grid visually */
	void StartDraggingItem(UItem* Item);
	/** Called when drag failed. Puts item back into the grid*/
	void CancelDraggingItem();
	/** Called when dragged item dropped not into the same grid. Removes dragged item completely */
	void FinishDraggingItemOutOfGrid();
	/** Called when dragged item dropped into the same grid. Changes dragged item's coordinates */
	void MoveDraggingItemInSameGrid(FIntPoint Coordinates);

	UPROPERTY(BlueprintAssignable)
	FOnGridChange OnGridChange;

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	TArray<UItem*> GetItems()const { return Items; }
	FIntPoint GetSize()const { return Size; }

private:
	/** functions for working with one-dimensional array as with two-dimensional and otherwise */

	uint32 GetCell(FIntPoint Coordinates)const { return Cells[GetIndex(Coordinates)]; }
	int32 GetIndex(FIntPoint Coordinates)const { return Coordinates.Y * Size.X + Coordinates.X; }
	int32 GetColumn(int32 Index)const { return Index % Size.X; }
	int32 GetRow(int32 Index)const { return Index / Size.X; }

	void AllocateCells();

	void AddItemAndBroadcast(UItem* Item, FIntPoint Coordinates);
	void RemoveItemAndBroadcast(UItem* Item);

	void AddItemInternal(UItem* Item, FIntPoint Coordinates);
	void RemoveItemInternal(UItem* Item);

	UPROPERTY(VisibleAnywhere)
	FIntPoint Size;

	UPROPERTY(VisibleAnywhere)
	TArray<UItem*> Items;

	UPROPERTY(VisibleAnywhere)
	TArray<uint32> Cells;

	UPROPERTY()
	UItem* DraggingItem;
};
