// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "StatsAndAttributes/StatCollection.h"
#include "StatsAndAttributes/Stat.h"
#include "StatsAndAttributes/Resource.h"

UStatCollection::UStatCollection()
{
	
}

void UStatCollection::Init()
{
	InitStats();
	//InitResources();
}

void UStatCollection::InitResources()
{
	UResource* HealthResource = UResource::Create(Stats[StatToInt(EStat::MaxHealth)], EResource::Health,
	                                              NSLOCTEXT("Stats", "Health", "Current Health"));
	Resources.Insert(HealthResource, static_cast<int32>(EResource::Health));

	UResource* ManaResource = UResource::Create(Stats[StatToInt(EStat::MaxMana)], EResource::Mana,
	                                            NSLOCTEXT("Stats", "Mana", "Current Mana"));
	Resources.Insert(ManaResource, static_cast<int32>(EResource::Mana));
}

void UStatCollection::InitStats()
{
	UStat* ArmorStat = UStat::Create(0.f, EStat::Armor,
	                                 NSLOCTEXT("Stats", "Armor", "Armor"), 0.f, 85.f);
	Stats.Insert(ArmorStat, static_cast<int32>(EStat::Armor));

	UStat* MaxHealthStat = UStat::Create(100.f, EStat::MaxHealth,
	                                     NSLOCTEXT("Stats", "MaxHealth", "Maximum Health"), 0.f);
	Stats.Insert(MaxHealthStat, static_cast<int32>(EStat::MaxHealth));

	UStat* MaxManaStat = UStat::Create(100.f, EStat::MaxMana,
	                                   NSLOCTEXT("Stats", "MaxMana", "Maximum Mana"), 0.f);
	Stats.Insert(MaxManaStat, static_cast<int32>(EStat::MaxMana));

	UStat* MinDamageStat = UStat::Create(10.f, EStat::MinDamage,
	                                     NSLOCTEXT("Stats", "MinDamage", "Minimum Damage"), 0.f);
	Stats.Insert(MinDamageStat, static_cast<int32>(EStat::MinDamage));

	UStat* MaxDamageStat = UStat::Create(10.f, EStat::MaxDamage,
	                                     NSLOCTEXT("Stats", "MaxDamage", "Maximum Damage"), 0.f);
	Stats.Insert(MaxDamageStat, static_cast<int32>(EStat::MaxDamage));

	UStat* DamageMultiplierStat = UStat::Create(1.f, EStat::DamageMultiplier,
	                                            NSLOCTEXT("Stats", "DamageMultiplier", "Additional Damage Percent"), 0.01f);
	Stats.Insert(DamageMultiplierStat, static_cast<int32>(EStat::DamageMultiplier));

	UStat* AttackSpeedStat = UStat::Create(0.f, EStat::AttackSpeed,
	                                       NSLOCTEXT("Stats", "AttackSpeed", "Additional Attack Speed Percent"), -100.f, 75.f);
	Stats.Insert(AttackSpeedStat, static_cast<int32>(EStat::AttackSpeed));

	UStat* MoveSpeedStat = UStat::Create(100.f, EStat::MoveSpeed,
	                                     NSLOCTEXT("Stats", "MoveSpeed", "Movement Speed"), 0.f, 200.f);
	Stats.Insert(MoveSpeedStat, static_cast<int32>(EStat::MoveSpeed));

	UStat* HealthRegenStat = UStat::Create(0.f, EStat::HealthRegen,
	                                       NSLOCTEXT("Stats", "HealthRegen", "Health Regeneration"), 0.f);
	Stats.Insert(HealthRegenStat, static_cast<int32>(EStat::HealthRegen));

	UStat* ManaRegenStat = UStat::Create(0.f, EStat::ManaRegen,
	                                     NSLOCTEXT("Stats", "ManaRegen", "Mana Regeneration"), 0.f);
	Stats.Insert(ManaRegenStat, static_cast<int32>(EStat::ManaRegen));
}

void UStatCollection::PostInitProperties()
{
	Super::PostInitProperties();
	
	//InitStats();
}
