// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemGrid.generated.h"

#define EMPTY_CELL 0

class UItem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridChange);

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
	 * @brief Set particular cell in a grid with Id
	 * @param Coordinates - place where to set Id
	 * @param Id - Id to set
	 */
	void SetCell(FIntPoint Coordinates, uint32 Id);

	/** Fill area in grid with given Id */
	void FillArea(FIntPoint TopLeftPoint, FIntPoint AreaSize, uint32 Id);

	/**
	 * @return grid coordinates or FIntPoint::NoneValue if empty area isn't found
	 */
	FIntPoint FindEmptyAreaCoordinates(FIntPoint ItemSize);

	/**
	 * @brief true if there is no other items or borders in given area
	 * @param GridCoordinates - Top left point of an item in inventory grid
	 * @param ItemSize - how much cells to check for an item to fit
	 * */
	bool IsAreaEmpty(FIntPoint GridCoordinates, FIntPoint ItemSize) const;

	void AddItemInternal(UItem* Item, FIntPoint Coordinates);
	void RemoveItemInternal(UItem* Item);

	UPROPERTY(BlueprintAssignable)
	FOnGridChange OnGridChange;

	TArray<UItem*> GetItems()const { return Items; }

	/** functions for working with one-dimensional array as with two-dimensional and otherwise */

	uint32 GetCell(FIntPoint Coordinates)const { return Cells[GetIndex(Coordinates)]; }
	int32 GetIndex(FIntPoint Coordinates)const { return Coordinates.Y * Size.X + Coordinates.X; }
	int32 GetColumn(int32 Index)const { return Index % Size.X; }
	int32 GetRow(int32 Index)const { return Index / Size.X; }

private:
	void AllocateCells();

	UPROPERTY(VisibleAnywhere)
	FIntPoint Size;

	UPROPERTY(VisibleAnywhere)
	TArray<UItem*> Items;

	UPROPERTY(VisibleAnywhere)
	TArray<uint32> Cells;
};
