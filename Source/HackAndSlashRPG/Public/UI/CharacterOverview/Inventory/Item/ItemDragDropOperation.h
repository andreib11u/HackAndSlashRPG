// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UItemGrid;
class UItem;
/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UItem* Item;
};
