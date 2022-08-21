// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

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


private:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* VisualGrid;
	UPROPERTY(meta = (BindWidget))
	USizeBox* GridSize;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* GridCanvas;

	UFUNCTION()
	void OnItemGridUpdate();

	void CreateGrid(FIntPoint Size);
	void CreateItemWidgets(const TArray<UItem*>& Items);

	UPROPERTY()
	UItemGrid* DisplayingGrid;

	const float CellSize = 60.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CellWidgetClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemWidget> ItemWidgetClass;
};
