// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Utility/RPGEnums.h"
#include "Attributes.generated.h"

class APlayerCharacter;
class UStatCollection;
class UPlayerAttribute;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPointsChange, int32)
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

	UPlayerAttribute* GetAttribute(EAttribute Attribute) { return Attributes[EnumToInt(Attribute)]; }

	int32 GetPoints()const { return Points; }
	void SetPoints(int32 InPoints);
	FOnPointsChange OnPointsChange;
private:
	UPROPERTY()
	UStatCollection* AffectedStats;

	/**	Points which player can spend on attributes */
	UPROPERTY(EditAnywhere)
	int32 Points = 0;

	UFUNCTION()
	void OnStrengthChanged(int32 NewStrength);

	UFUNCTION()
	void OnAgilityChanged(int32 NewAgility);

	UFUNCTION()
	void OnIntelligenceChanged(int32 NewIntelligence);

	UFUNCTION()
	void OnVitalityChanged(int32 NewVitality);
};
