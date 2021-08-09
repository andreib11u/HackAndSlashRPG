// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "GameplayFramework/HackAndSlashPlayerController.h"

#include "Characters/BaseCharacter.h"
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
			auto MoveCommand = NewObject<UMoveCommand>();
			const auto CastedOwner = Cast<ABaseCharacter>(GetPawn());
			MoveCommand->Init(OutHit.Location, CastedOwner);
			CommandExecutorComponent->ExecuteCommand(MoveCommand);
		}
	}
}
