// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Utility/RPGEnums.h"
#include "PlayerAttribute.generated.h"

class UAttributes;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttributeChange, int32);

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API UPlayerAttribute : public UObject
{
	GENERATED_BODY()
public:
	static UPlayerAttribute* Create(int32 InValue, FText InName, EAttribute InType, UAttributes* InAttributes);

	int32 Get()const { return Value; }
	void SetValue(int32 InValue);
	void ChangeValue(int32 InValue);

	EAttribute GetType()const { return Type; }
	UAttributes* GetOwningAttributes()const { return OwningAttributes; }

	FOnAttributeChange OnAttributeChange;

	
private:
	UPROPERTY(VisibleAnywhere)
	int32 Value = 10;

	UPROPERTY(VisibleAnywhere)
	EAttribute Type;

	UPROPERTY(VisibleAnywhere)
	FText Name;

	UPROPERTY(VisibleInstanceOnly)
	UAttributes* OwningAttributes;

};
