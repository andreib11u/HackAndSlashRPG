// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UItemGrid;
class UItem;
/**
 * Manages UItemGrids. You can add or remove items directly to a grid or
 * through this component. Also manages default items that added at the start.
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASHRPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItem(UItem* Item);

	UFUNCTION(BlueprintCallable)
	bool AddManyItems(TArray<UItem*> Items, TArray<UItem*>& OutNotAddedItems);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(UItem* Item);

	void AddGrid(UItemGrid* Grid) { Grids.Add(Grid); }
	UItemGrid* GetGridAt(int32 Index) { return Grids[Index]; }

protected:
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;

private:
	void AddDefaultGrid();
	void AddDefaultItems();

	/**	Added to this inventory at the start */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<UItem*> DefaultItems;

	UPROPERTY(VisibleInstanceOnly)
	TArray<UItemGrid*> Grids;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FIntPoint DefaultGridSize = FIntPoint(10, 6);
};
