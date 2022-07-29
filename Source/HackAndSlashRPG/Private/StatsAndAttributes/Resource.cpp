// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "StatsAndAttributes/Resource.h"
#include "StatsAndAttributes/Stat.h"

UResource::UResource()
{
	
}

UResource* UResource::Create(float InitialValue, EResource InType, FText InName)
{
	FName ResourceName = MakeUniqueObjectName(GetTransientPackage(), StaticClass(), FName(InName.ToString()));

	UResource* NewResource = NewObject<UResource>(GetTransientPackage(), ResourceName);
	NewResource->MinValue = 0.f;
	NewResource->MaxValue = InitialValue;
	NewResource->Name = InName;
	NewResource->Type = InType;
	NewResource->InitialValue  = InitialValue;
	NewResource->Value  = InitialValue;
	return NewResource;
}

void UResource::ChangeValue(float Change)
{
	const float ValueBefore = Value;
	Value = FMath::Clamp(Value + Change, MinValue, MaxValue);
	
	if (ValueBefore != Value)
	{
		OnChange.Broadcast(Value);
	}
	
	if (Value == MinValue)
	{
		OnDeplete.Broadcast();
	}
}

void UResource::SetValue(float ValueToSet)
{
	const float ValueBefore = Value;
	Value = FMath::Clamp(ValueToSet, MinValue, MaxValue);

	if (ValueBefore != Value)
	{
		OnChange.Broadcast(Value);
	}

	if (Value == MinValue)
	{
		OnDeplete.Broadcast();
	}
}

void UResource::OnDependentStatChange(float NewValue)
{
	MaxValue = NewValue;
}
