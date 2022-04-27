// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/AttributeLabel.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UAttributeLabel::Init(FText Name, int32 CurrentNumber, bool HavePointsToSpend)
{
	AttributeName->SetText(Name);
	AttributeNumber->SetText(FText::AsNumber(CurrentNumber));
	HavePointsToSpend ? AddAttributeButton->SetVisibility(ESlateVisibility::Visible) :
						AddAttributeButton->SetVisibility(ESlateVisibility::Hidden);
}
