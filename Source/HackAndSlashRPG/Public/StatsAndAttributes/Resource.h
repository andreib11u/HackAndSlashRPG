// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Utility/RPGEnums.h"
#include "Resource.generated.h"

class UStat;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeResource, float);
DECLARE_MULTICAST_DELEGATE(FOnDeplete);

/**
 * Health, mana etc.
 */
UCLASS(BlueprintType)
class HACKANDSLASHRPG_API UResource : public UObject
{
	GENERATED_BODY()
public:
	UResource();

	static UResource* Create(float InitialValue, EResource InType, FText InName);
	
	UFUNCTION(BlueprintPure)
	float Get()const { return Value; }

	friend class UStatCollection;

	UFUNCTION(BlueprintCallable)
	void ChangeValue(float Change);

	UFUNCTION(BlueprintCallable)
	void SetValue(float ValueToSet);


	FOnChangeResource OnChange;

	FOnDeplete OnDeplete;

	UFUNCTION(BlueprintCallable)
	void OnDependentStatChange(float NewValue);
	
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InitialValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxValue = TNumericLimits<float>::Max();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MinValue = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EResource Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText Name;
};
