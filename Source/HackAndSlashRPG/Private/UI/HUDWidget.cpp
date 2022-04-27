// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "UI/HUDWidget.h"
#include "Components/StatsComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "StatsAndAttributes/Resource.h"
#include "StatsAndAttributes/StatCollection.h"
#include "StatsAndAttributes/Stat.h"

void UHUDWidget::SetCharacterToDisplay(APlayerCharacter* PlayerCharacter)
{
	UStat* MaxHealth = PlayerCharacter->GetStat(EStat::MaxHealth);
	UStat* MaxMana = PlayerCharacter->GetStat(EStat::MaxMana);
	UResource* Health = PlayerCharacter->GetResource(EResource::Health);
	UResource* Mana = PlayerCharacter->GetResource(EResource::Mana);

	MaxHealth->OnChange.AddDynamic(this, &UHUDWidget::OnMaxHealthChange);
	MaxMana->OnChange.AddDynamic(this, &UHUDWidget::OnMaxManaChange);

	Health->OnChange.AddDynamic(this, &UHUDWidget::OnHealthChange);
	Mana->OnChange.AddDynamic(this, &UHUDWidget::OnManaChange);

	OnHealthChange(Health->Get());
	OnMaxHealthChange(MaxHealth->Get());

	OnManaChange(Mana->Get());
	OnMaxManaChange(MaxMana->Get());
}

void UHUDWidget::UpdateHealthBar()
{
	const float Percent = CurrentHealth / CurrentMaxHealth;

	HealthBar->SetPercent(Percent);

	HealthBar->SetFillColorAndOpacity(FColor::MakeRedToGreenColorFromScalar(Percent));

	HealthText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), static_cast<int>(CurrentHealth), static_cast<int>(CurrentMaxHealth))));
}

void UHUDWidget::OnHealthChange(const float Health)
{
	CurrentHealth = Health;
	
	UpdateHealthBar();
}

void UHUDWidget::UpdateManaBar()
{
	const float Percent = CurrentMana / CurrentMaxMana;

	ManaBar->SetPercent(Percent);

	ManaText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), static_cast<int>(CurrentMana), static_cast<int>(CurrentMaxMana))));
}

void UHUDWidget::OnManaChange(const float Mana)
{
	CurrentMana = Mana;
	
	UpdateManaBar();
}

void UHUDWidget::OnMaxHealthChange(const float MaxHealth)
{
	CurrentMaxHealth = MaxHealth;

	UpdateHealthBar();
}

void UHUDWidget::OnMaxManaChange(const float MaxMana)
{
	CurrentMaxMana = MaxMana;

	UpdateManaBar();
}