// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "UI/CharacterOverview/ShowCharacterOverviewWidget.h"
#include "UI/CharacterOverview/CharacterOverviewWidget.h"

void UShowCharacterOverviewWidget::Init(APlayerCharacter* CharacterToDisplay)
{
	WidgetToShow->Init(CharacterToDisplay);
	PlayAnimation(ShowWidget);
	OnWidgetAnimationChanged.BindDynamic(this, &UShowCharacterOverviewWidget::OnShowWidgetAnimationEnd);
}

void UShowCharacterOverviewWidget::Close()
{
	// Play animation and close after the animations ends
	BindToAnimationFinished(ShowWidget, OnWidgetAnimationChanged);
	PlayAnimationReverse(ShowWidget);
}

void UShowCharacterOverviewWidget::OnShowWidgetAnimationEnd()
{
	RemoveFromParent();
}
