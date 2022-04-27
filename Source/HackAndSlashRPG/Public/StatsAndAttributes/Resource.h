// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resource.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EResource : uint8
{
	Health UMETA(DisplayName = "Health"),
	Mana   UMETA(DisplayName = "Mana")
};

int32 static ResourceToInt(EResource Resource)
{
	return static_cast<int32>(Resource);
}

class UStat;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeResource, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeplete);

/**
 * Health, mana etc.
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class HACKANDSLASHRPG_API UResource : public UObject
{
	GENERATED_BODY()
public:
	UResource();

	static UResource* Create(UStat* DependentStat, EResource InType, FText InName);
	
	UFUNCTION(BlueprintPure)
	float Get()const { return Value; }

	UFUNCTION(BlueprintCallable)
	void ChangeValue(float Change);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnChangeResource OnChange;
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
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
