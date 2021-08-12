// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "GameplayFramework/HackAndSlashPlayerController.h"

#include "Characters/BaseCharacter.h"
#include "Characters/EnemyCharacter.h"
#include "Commands/AttackCommand.h"
#include "Commands/MoveCommand.h"
#include "Components/CommandExecutorComponent.h"

void AHackAndSlashPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AHackAndSlashPlayerController::SetDestination);
}

void AHackAndSlashPlayerController::SetDestination()
{
	auto CommandExecutorComponent = Cast<UCommandExecutorComponent>(GetPawn()->GetComponentByClass(UCommandExecutorComponent::StaticClass()));
	if (CommandExecutorComponent)
	{		
		FHitResult OutHit;
		if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit))
		{
			const auto CastedPawn = Cast<ABaseCharacter>(GetPawn());
			auto Enemy = Cast<AEnemyCharacter>(OutHit.GetActor());
			if (Enemy)
			{
				const float TargetDistance = FVector::Distance(GetPawn()->GetActorLocation(), Enemy->GetActorLocation());
				auto AttackCommand = NewObject<UAttackCommand>();
				AttackCommand->Init(CastedPawn, Enemy);
				if (TargetDistance < CastedPawn->GetStartingAttackDistance())
				{					
					CommandExecutorComponent->ExecuteCommand(AttackCommand);
				}
				else
				{
					auto MoveCommand = NewObject<UMoveCommand>();
					MoveCommand->Init(OutHit.GetActor(), CastedPawn);
					CommandExecutorComponent->ExecuteCommand(MoveCommand);
					CommandExecutorComponent->AddToBuffer(AttackCommand);
				}
			}
			else
			{
				auto MoveCommand = NewObject<UMoveCommand>();			
				if (CastedPawn)
				{
					MoveCommand->Init(OutHit.Location, CastedPawn);
					CommandExecutorComponent->ExecuteCommand(MoveCommand);
				}
			}
		}
	}
}

void AHackAndSlashPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetShowMouseCursor(true);
}
