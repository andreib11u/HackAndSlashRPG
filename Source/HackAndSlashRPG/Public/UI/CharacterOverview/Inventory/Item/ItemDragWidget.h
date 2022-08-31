// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDragWidget.generated.h"

class UItem;
class USizeBox;
class UImage;
/**
 * Dragged item widget
 */
UCLASS()
class HACKANDSLASHRPG_API UItemDragWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(UItem* DraggedItem);
private:
	UPROPERTY(meta = (BindWidget))
	USizeBox* ItemSizeBox;
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;
};
