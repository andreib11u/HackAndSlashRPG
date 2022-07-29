// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "StatsAndAttributes/Stat.h"

UStat::UStat()
{
	ClampedValue = FMath::Clamp(InitialValue, MinValue, MaxValue);
	OverflowValue = ClampedValue;
}

void UStat::SetInitialValue(float InInitialValue)
{
	InitialValue = InInitialValue;
	SetValue(InInitialValue);
}

void UStat::SetValue(float InValue)
{
	ClampedValue = FMath::Clamp(InValue, MinValue, MaxValue);
	OverflowValue = ClampedValue;
	OnChange.Broadcast(ClampedValue);
}

UStat* UStat::Create(float InInitialValue, EStat InType, FText InName, float InMinValue, float InMaxValue)
{
	FName StatName = MakeUniqueObjectName(GetTransientPackage(), StaticClass(), FName(InName.ToString()));

	UStat* NewStat = NewObject<UStat>(GetTransientPackage(), StatName);
	NewStat->MaxValue = InMaxValue;
	NewStat->MinValue = InMinValue;
	NewStat->SetInitialValue(InInitialValue);
	NewStat->Type = InType;
	NewStat->Name = InName;
	return NewStat;
}

void UStat::Add(float Value)
{
	OverflowValue = OverflowValue + Value;
	ClampedValue = FMath::Clamp(OverflowValue, MinValue, MaxValue);
	OnChange.Broadcast(ClampedValue);
}

void UStat::Remove(float Value)
{
	OverflowValue = OverflowValue - Value;
	ClampedValue = FMath::Clamp(OverflowValue, MinValue, MaxValue);
	OnChange.Broadcast(ClampedValue);
}
