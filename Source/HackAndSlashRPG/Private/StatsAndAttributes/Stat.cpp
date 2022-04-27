// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "StatsAndAttributes/Stat.h"

UStat::UStat()
{
	ClampedValue = FMath::Clamp(InitialValue, MinValue, MaxValue);
	OverflowValue = ClampedValue;
}

void UStat::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UStat, InitialValue))
	{
		SetInitialValue(InitialValue);
	}
}

void UStat::SetInitialValue(float InInitialValue)
{
	InitialValue = InInitialValue;
	ClampedValue = FMath::Clamp(InitialValue, MinValue, MaxValue);
	OverflowValue = ClampedValue;
}

UStat* UStat::Create(float InInitialValue, EStat InType, FText InName, float InMinValue, float InMaxValue)
{
	UStat* NewStat = NewObject<UStat>();
	NewStat->MaxValue = InMaxValue;
	NewStat->MinValue = InMinValue;
	NewStat->SetInitialValue(InInitialValue);
	NewStat->Type = InType;
	NewStat->Name = InName;
	return NewStat;
}

void UStat::AddChange(float Value)
{
	OverflowValue = OverflowValue + Value;
	ClampedValue = FMath::Clamp(OverflowValue, MinValue, MaxValue);
	OnChange.Broadcast(ClampedValue);
}

void UStat::RemoveChange(float Value)
{
	OverflowValue = OverflowValue - Value;
	ClampedValue = FMath::Clamp(OverflowValue, MinValue, MaxValue);
	OnChange.Broadcast(ClampedValue);
}
