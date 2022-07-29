// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatCollection.generated.h"

class UResource;
class UStat;
/**
 * Contains stats in a map and applies modificators
 */
UCLASS(Blueprintable, BlueprintType)
class HACKANDSLASHRPG_API UStatCollection : public UObject
{
	GENERATED_BODY()
public:
	UStatCollection();

	void Init();

	void UpdateResources();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UStat*> Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UResource*> Resources;

private:
	void InitStats();
	void InitResources();
};
