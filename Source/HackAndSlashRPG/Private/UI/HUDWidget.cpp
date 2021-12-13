// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "UI/HUDWidget.h"
#include "Components/StatsComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHUDWidget::SetCharacterToDisplay(APlayerCharacter* PlayerCharacter)
{
	auto Stats = PlayerCharacter->FindComponentByClass<UStatsComponent>();

	Stats->OnHealthChange.AddDynamic(this, &UHUDWidget::OnHealthChange);
	Stats->OnManaChange.AddDynamic(this, &UHUDWidget::OnManaChange);

	const FCharacterStats CurrentStats = Stats->GetStats();
	OnHealthChange(CurrentStats.CurrentHealth, CurrentStats.MaxHealth);
	OnManaChange(CurrentStats.CurrentMana, CurrentStats.MaxMana);
}

void UHUDWidget::OnHealthChange(const float CurrentHealth, const float MaxHealth)
{
	const float Percent = CurrentHealth / MaxHealth;

	HealthBar->SetPercent(Percent);

	HealthBar->SetFillColorAndOpacity(FColor::MakeRedToGreenColorFromScalar(Percent));

	HealthText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), static_cast<int>(CurrentHealth), static_cast<int>(MaxHealth))));
}

void UHUDWidget::OnManaChange(const float CurrentMana, const float MaxMana)
{
	const float Percent = CurrentMana / MaxMana;

	ManaBar->SetPercent(Percent);

	ManaText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), static_cast<int>(CurrentMana), static_cast<int>(MaxMana))));
}
