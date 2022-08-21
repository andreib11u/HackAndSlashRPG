// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "Items/Item.h"

FLinearColor UItem::GetColorFromRarity(EItemRarity Rarity)
{
	switch (Rarity)
	{
	case EItemRarity::Common: 
		return FLinearColor(FColor(128, 127, 125, 225));
	case EItemRarity::Uncommon: 
		return FLinearColor(FColor(50, 113, 168, 225));
	case EItemRarity::Rare:
		return FLinearColor(FColor(176, 170, 5, 225));
	case EItemRarity::Legendary:
		return FLinearColor(FColor(212, 100, 15, 225));
	default:
		checkNoEntry();
		return FLinearColor::Black;
	}

}

UTexture2D* UItem::GetImage() const
{
	if (Image.IsPending())
	{
		return Image.LoadSynchronous();
	}
	return Image.Get();
}


UStaticMesh* UItem::GetMesh() const
{
	if (Mesh.IsPending())
	{
		return Mesh.LoadSynchronous();
	}
	return Mesh.Get();
}
