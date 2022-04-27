// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "StatsAndAttributes/Resource.h"
#include "StatsAndAttributes/Stat.h"

UResource::UResource()
{
	
}

UResource* UResource::Create(UStat* DependentStat, EResource InType, FText InName)
{
	UResource* NewResource = NewObject<UResource>();
	NewResource->MinValue = 0.f;
	NewResource->MaxValue = DependentStat->Get();
	NewResource->Name = InName;
	NewResource->Type = InType;
	NewResource->InitialValue  = DependentStat->Get();
	NewResource->Value  = DependentStat->Get();
	DependentStat->OnChange.AddDynamic(NewResource, &UResource::OnDependentStatChange);
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

void UResource::OnDependentStatChange(float NewValue)
{
	MaxValue = NewValue;
}
