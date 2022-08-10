// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "Items/Item.h"

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
