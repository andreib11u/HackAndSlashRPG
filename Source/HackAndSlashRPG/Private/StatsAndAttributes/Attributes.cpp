// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "StatsAndAttributes/Attributes.h"

#include "Characters/PlayerCharacter.h"
#include "StatsAndAttributes/PlayerAttribute.h"
#include "StatsAndAttributes/Resource.h"
#include "StatsAndAttributes/Stat.h"
#include "StatsAndAttributes/StatCollection.h"


void UAttributes::Init(APlayerCharacter* Character)
{
	UPlayerAttribute* Strength = UPlayerAttribute::Create(Character->InitialStrength,
		NSLOCTEXT("Attributes", "Strength", "Strength"), EAttribute::Strength, this);
	UPlayerAttribute* Agility = UPlayerAttribute::Create(Character->InitialAgility,
		NSLOCTEXT("Attributes", "Agility", "Agility"), EAttribute::Agility, this);
	UPlayerAttribute* Intelligence = UPlayerAttribute::Create(Character->InitialIntelligence,
		NSLOCTEXT("Attributes", "Intelligence", "Intelligence"), EAttribute::Intelligence, this);
	UPlayerAttribute* Vitality = UPlayerAttribute::Create(Character->InitialVitality,
		NSLOCTEXT("Attributes", "Vitality", "Vitality"), EAttribute::Vitality, this);

	Attributes.Add(Strength);
	Attributes.Add(Agility);
	Attributes.Add(Intelligence);
	Attributes.Add(Vitality);

	AffectedStats = Character->GetStats();

	Strength->OnAttributeChange.AddUObject(this, &UAttributes::OnStrengthChanged);
	Agility->OnAttributeChange.AddUObject(this, &UAttributes::OnAgilityChanged);
	Intelligence->OnAttributeChange.AddUObject(this, &UAttributes::OnIntelligenceChanged);
	Vitality->OnAttributeChange.AddUObject(this, &UAttributes::OnVitalityChanged);

	OnStrengthChanged(Strength->Get());
	OnAgilityChanged(Agility->Get());
	OnIntelligenceChanged(Intelligence->Get());
	OnVitalityChanged(Vitality->Get());

	// Heal to full hp
	// TODO: make a stats method that fulls every resource
	AffectedStats->Resources[EnumToInt(EResource::Health)]->SetValue(AffectedStats->Stats[EnumToInt(EStat::MaxHealth)]->Get());
	AffectedStats->Resources[EnumToInt(EResource::Mana)]->SetValue(AffectedStats->Stats[EnumToInt(EStat::MaxMana)]->Get());
}

void UAttributes::SetPoints(int32 InPoints)
{
	Points = InPoints;
	OnPointsChange.Broadcast(Points);
}

void UAttributes::OnStrengthChanged(int32 NewStrength)
{
	UStat* DamageMultiplier = AffectedStats->Stats[EnumToInt(EStat::DamageMultiplier)];
	DamageMultiplier->SetValue(NewStrength * 0.01f);

	// TODO: recalcualte modificators 
}

void UAttributes::OnAgilityChanged(int32 NewAgility)
{
	UStat* AttackSpeed = AffectedStats->Stats[EnumToInt(EStat::AttackSpeed)];
	AttackSpeed->SetValue(NewAgility);
}

void UAttributes::OnIntelligenceChanged(int32 NewIntelligence)
{
	UStat* MaxMana = AffectedStats->Stats[EnumToInt(EStat::MaxMana)];
	MaxMana->SetValue(NewIntelligence * 7.f);
}

void UAttributes::OnVitalityChanged(int32 NewVitality)
{
	UStat* MaxHealth = AffectedStats->Stats[EnumToInt(EStat::MaxHealth)];
	MaxHealth->SetValue(NewVitality * 12.f);
}
