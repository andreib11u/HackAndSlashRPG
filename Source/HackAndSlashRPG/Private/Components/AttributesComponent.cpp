// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Components/AttributesComponent.h"

UAttributesComponent::UAttributesComponent()
{

}

void UAttributesComponent::SpendPointsOnAttribute(const EAttribute Attribute, const int32 Points)
{
	if (PointsToSpend > 0)
	{
		if (Points > PointsToSpend)
		{
			AddAttribute(Attribute, PointsToSpend);
			PointsToSpend = 0;
		}
		else
		{
			AddAttribute(Attribute, Points);
			PointsToSpend -= Points;
		}
	}
}

int32& UAttributesComponent::GetAttributeReference(const EAttribute Attribute)
{
	switch (Attribute)
	{
	case EAttribute::Strength:
		return Attributes.Strength;
	case EAttribute::Agility:
		return Attributes.Agility;
	case EAttribute::Intelligence:
		return Attributes.Intelligence;
	case EAttribute::Vitality:
		return Attributes.Vitality;
	default:
		checkNoEntry();
		return Attributes.Agility;
	}	
}

void UAttributesComponent::BroadcastMessage(const EAttribute Attribute, const int32 Points)
{
	switch (Attribute)
	{
	case EAttribute::Strength:
		OnStrengthChange.Broadcast(Points);
		break;
	case EAttribute::Agility:
		OnAgilityChange.Broadcast(Points);
		break;
	case EAttribute::Intelligence:
		OnIntelligenceChange.Broadcast(Points);
		break;
	case EAttribute::Vitality:
		OnVitalityChange.Broadcast(Points);
		break;
	default:
		checkNoEntry();
		break;
	}
}

void UAttributesComponent::AddAttribute(const EAttribute Attribute, const int32 Points)
{
	int32& AttributeValue = GetAttributeReference(Attribute);

	AttributeValue += Points;

	BroadcastMessage(Attribute, Points);
}

void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	Attributes = InitialAttributes;
	
}

