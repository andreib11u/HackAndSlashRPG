// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemState : uint8
{
	None UMETA(DisplayName = "None"),
	Inventory UMETA(DisplayName = "Inventory"),
	Equipment UMETA(DisplayName = "Equipment"),
	Mesh UMETA(DisplayName = "Mesh")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Legendary UMETA("Legendary")
};

class UItemGrid;
/**
 * Game item. To create an item, derive a blueprint from this or other
 * abstract item classes. Items can be added to item grids within inventory components,
 * added to an equipment slot, or exist as a pickup mesh.
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew)
class HACKANDSLASHRPG_API UItem : public UObject
{
	GENERATED_BODY()
public:


	FText GetItemName()const { return Name; }
	FText GetDescription()const { return Description; }
	UTexture2D* GetImage()const;
	UStaticMesh* GetMesh()const;
	FIntPoint GetSize()const { return Size; }
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (Multiline = "true", AllowPrivateAccess = "true"))
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> Image;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UStaticMesh> Mesh;
	// X - Width; Y - Height
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	FIntPoint Size;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (ClampMin = 1, AllowPrivateAccess = "true"))
	int32 MaxQuantity = 1;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = 1, AllowPrivateAccess = "true"))
	int32 Quantity = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = 0, AllowPrivateAccess = "true"))
	int32 Price;

	UPROPERTY()
	UItemGrid* OwningGrid;
	UPROPERTY()
	FIntPoint GridCoordinates;
};
