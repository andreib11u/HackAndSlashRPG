// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemDragDropOperation.h"
#include "InventoryWidget.generated.h"

class UItemHintWidget;
class UItemWidget;
class UItem;
class UUniformGridPanel;
class UCanvasPanel;
class USizeBox;
class UGridPanel;
class UItemGrid;
/**
 * Displays items in a grid
 */
UCLASS()
class HACKANDSLASHRPG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(UItemGrid* ItemGrid);

protected:
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* VisualGrid;
	UPROPERTY(meta = (BindWidget))
	USizeBox* GridSize;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* GridCanvas;

	UPROPERTY()
	TArray<UItemWidget*> ItemWidgets;

	UPROPERTY()
	UItemHintWidget* Hint;

	UFUNCTION()
	void OnItemGridUpdate();

	void CreateGrid(FIntPoint Size);
	void CreateItemWidgets(const TArray<UItem*>& Items);
	void RemoveItemWidgets();

	FIntPoint GetGridCoordinatesFromDraggedItem(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UItemDragDropOperation* ItemDragDropOp);
	FIntPoint LocalToGrid(FVector2D LocalPosition);
	bool IsDraggedItemInBorders(FIntPoint GridCoordinates, FIntPoint ItemSize);

	void ShowItemHint(FIntPoint Coordinates, FIntPoint ItemSize, FLinearColor Color);
	void RemoveHint();

	UPROPERTY()
	UItemGrid* DisplayingGrid;

	const float CellSize = 60.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CellWidgetClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemWidget> ItemWidgetClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemHintWidget> ItemHintWidgetClass;
};

