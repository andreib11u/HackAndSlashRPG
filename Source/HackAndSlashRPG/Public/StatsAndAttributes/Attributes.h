// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Attributes.generated.h"

class APlayerCharacter;
class UStatCollection;
class UPlayerAttribute;
/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UAttributes : public UObject
{
	GENERATED_BODY()

public:
	void Init(APlayerCharacter* Character);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UPlayerAttribute*> Attributes;
private:
	UPROPERTY()
	UStatCollection* AffectedStats;

	UFUNCTION()
	void OnStrengthChanged(int32 NewStrength);

	UFUNCTION()
	void OnAgilityChanged(int32 NewAgility);

	UFUNCTION()
	void OnIntelligenceChanged(int32 NewIntelligence);

	UFUNCTION()
	void OnVitalityChanged(int32 NewVitality);
};
