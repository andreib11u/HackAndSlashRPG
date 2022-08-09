// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "StatsAndAttributes/PlayerAttribute.h"

UPlayerAttribute* UPlayerAttribute::Create(int32 InValue, FText InName, EAttribute InType, UAttributes* InAttributes)
{
	FName AttributeName = MakeUniqueObjectName(GetTransientPackage(), StaticClass(), FName(InName.ToString()));

	UPlayerAttribute* Result = NewObject<UPlayerAttribute>(GetTransientPackage(), AttributeName);
	Result->Name = InName;
	Result->Type = InType;
	Result->OwningAttributes = InAttributes;
	Result->SetValue(InValue);
	return Result;
}

void UPlayerAttribute::SetValue(int32 InValue)
{
	int32 ValueBefore = Value;
	Value = InValue;
	if (ValueBefore != Value)
	{
		OnAttributeChange.Broadcast(Value);
	}
}

void UPlayerAttribute::ChangeValue(int32 InValue)
{
	Value += InValue;
	OnAttributeChange.Broadcast(Value);
}
