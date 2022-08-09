// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/CharacterOverviewWidget.h"

#include "Characters/PlayerCharacter.h"
#include "UI/CharacterOverview/AttributesWidget.h"

void UCharacterOverviewWidget::Init(APlayerCharacter* CharacterToDisplay)
{
	Attributes->Init(CharacterToDisplay->GetAttributes());
}
