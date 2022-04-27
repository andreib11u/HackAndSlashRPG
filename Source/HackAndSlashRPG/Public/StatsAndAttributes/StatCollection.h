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
UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class HACKANDSLASHRPG_API UStatCollection : public UObject
{
	GENERATED_BODY()
public:
	
	UStatCollection();

	void Init();
	
	void InitResources(); // Call after base character configured stats
	void InitStats();

	virtual void PostInitProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta = (AllowPrivateAccess = "true"))
	TArray<UStat*> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta = (AllowPrivateAccess = "true"))
	TArray<UResource*> Resources;
};
