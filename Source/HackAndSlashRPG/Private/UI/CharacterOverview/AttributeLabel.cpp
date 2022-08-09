// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/AttributeLabel.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "StatsAndAttributes/Attributes.h"
#include "StatsAndAttributes/PlayerAttribute.h"

void UAttributeLabel::Init(UPlayerAttribute* AttributeToDisplay)
{
	AttributeName->SetText(FText::FromString(EnumToString(AttributeToDisplay->GetType())));
	AttributeNumber->SetText(FText::AsNumber(AttributeToDisplay->Get()));

	UAttributes* OwningAttributes = AttributeToDisplay->GetOwningAttributes();
	OwningAttributes->OnPointsChange.AddUObject(this, &UAttributeLabel::OnPointsChange);
	OnPointsChange(OwningAttributes->GetPoints());
}

void UAttributeLabel::OnPointsChange(int32 Points)
{
	if (Points > 0)
	{
		AddAttributeButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		AddAttributeButton->SetVisibility(ESlateVisibility::Hidden);
	}
}
