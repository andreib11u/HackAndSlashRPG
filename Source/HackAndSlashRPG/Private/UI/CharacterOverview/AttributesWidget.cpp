// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/AttributesWidget.h"

#include "StatsAndAttributes/Attributes.h"
#include "StatsAndAttributes/Stat.h"
#include "UI/CharacterOverview/AttributeLabel.h"

void UAttributesWidget::Init(UAttributes* AttributesToDisplay)
{
	StrengthAttributeLabel->Init(AttributesToDisplay->GetAttribute(EAttribute::Strength));
	AgilityAttributeLabel->Init(AttributesToDisplay->GetAttribute(EAttribute::Agility));
	IntelligenceAttributeLabel->Init(AttributesToDisplay->GetAttribute(EAttribute::Intelligence));
	VitalityAttributeLabel->Init(AttributesToDisplay->GetAttribute(EAttribute::Vitality));
}
