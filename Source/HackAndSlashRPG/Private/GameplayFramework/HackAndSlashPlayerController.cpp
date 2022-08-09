// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "GameplayFramework/HackAndSlashPlayerController.h"
#include "Abilities/BasicAttack.h"
#include "Blueprint/UserWidget.h"
#include "Characters/BaseCharacter.h"
#include "Characters/EnemyCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "Components/AbilityComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "UI/HUDWidget.h"
#include "UI/CharacterOverview/ShowCharacterOverviewWidget.h"

AHackAndSlashPlayerController::AHackAndSlashPlayerController()
{
	bEnableMouseOverEvents = true;
}

void AHackAndSlashPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AHackAndSlashPlayerController::SetDestination);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AHackAndSlashPlayerController::UnsetDestination);
	InputComponent->BindAction("ToggleCharacterOverview", IE_Pressed, this, &AHackAndSlashPlayerController::ToggleCharacterOverview);
}

void AHackAndSlashPlayerController::SetDestination()
{
	bDestinationSet = true;
}

void AHackAndSlashPlayerController::UnsetDestination()
{
	bDestinationSet = false;
	UnsetEnemy();
}

void AHackAndSlashPlayerController::FindPathFollowingComponent()
{
	PathFollowingComp = FindComponentByClass<UPathFollowingComponent>();
	if (PathFollowingComp == nullptr)
	{
		PathFollowingComp = NewObject<UPathFollowingComponent>(this);
		PathFollowingComp->RegisterComponentWithWorld(GetWorld());
		PathFollowingComp->Initialize();
	}
}

void AHackAndSlashPlayerController::InitializeHUD()
{
	auto HUDWidget = CreateWidget<UHUDWidget>(this, *HUDClass);

	HUDWidget->SetCharacterToDisplay(ControlledCharacter);

	HUDWidget->AddToViewport();
}

void AHackAndSlashPlayerController::ConfigureAttackAbility()
{
	AttackAbility = NewObject<UBasicAttack>();

	AttackAbility->SetOwner(ControlledCharacter);
}

void AHackAndSlashPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);

	PlayerAbilityComponent = GetPawn()->FindComponentByClass<UAbilityComponent>();

	ControlledCharacter = Cast<APlayerCharacter>(GetCharacter());
	
	ConfigureAttackAbility();

	FindPathFollowingComponent();

	InitializeHUD();
}

void AHackAndSlashPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bDestinationSet)
	{
		if (Enemy) 
		{
			AttackAbility->SetTargetCharacter(Enemy);
			PlayerAbilityComponent->ExecuteAbility(AttackAbility);
		}
		else 
		{
			FHitResult OutHit;
			if (GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1/*MouseCursor*/, false, OutHit))
			{
				Enemy = Cast<AEnemyCharacter>(OutHit.GetActor());
				if (Enemy)
				{
					return;
				}

				ControlledCharacter->MoveTo(OutHit.Location);
			}
		}
	}
}

void AHackAndSlashPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearAllTimersForObject(this);
}

void AHackAndSlashPlayerController::AbortMove()
{
	if (PathFollowingComp)
	{
		PathFollowingComp->AbortMove(*GetPawn(), FPathFollowingResultFlags::MovementStop);
	}
}

void AHackAndSlashPlayerController::OnCloseWidgetAnimationEnd()
{
	OpenedCharacterOverview = nullptr;
}

void AHackAndSlashPlayerController::ToggleCharacterOverview()
{
	if (OpenedCharacterOverview)
	{
		OpenedCharacterOverview->Close();
		OpenedCharacterOverview = nullptr;
	}
	else
	{
		checkf(IsValid(ShowCharacterOverviewWidgetClass), TEXT("ShowCharacterOverviewWidgetClass is invalid. Set in BP_HackAndSlashPlayerController"))

		OpenedCharacterOverview = CreateWidget<UShowCharacterOverviewWidget>(this, *ShowCharacterOverviewWidgetClass);
		OpenedCharacterOverview->Init(ControlledCharacter);
		OpenedCharacterOverview->AddToViewport();
	}
}

void AHackAndSlashPlayerController::UnsetEnemy()
{
	Enemy = nullptr;
}
