// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Commands/MoveCommand.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HackAndSlashRPG/Public/Characters/BaseCharacter.h"
#include "Navigation/PathFollowingComponent.h"

void UMoveCommand::Init(FVector DestinationToSet, ABaseCharacter* OwnerToSet)
{
	SetOwner(OwnerToSet);
	Destination = DestinationToSet;
	PathFollowingComponent = GetPathFollowingComponent(*GetOwner()->GetController());

	if (PathFollowingComponent)
	{
		OnPathCompleteHandle = PathFollowingComponent->OnRequestFinished.AddUObject(this, &UMoveCommand::OnPathComplete);
	}
}

void UMoveCommand::Init(AActor* DestinationToSet, ABaseCharacter* OwnerToSet)
{
	SetOwner(OwnerToSet);
	DestinationActor = DestinationToSet;
	PathFollowingComponent = GetPathFollowingComponent(*GetOwner()->GetController());

	if (PathFollowingComponent)
	{
		OnPathCompleteHandle = PathFollowingComponent->OnRequestFinished.AddUObject(this, &UMoveCommand::OnPathComplete);
	}
}

void UMoveCommand::Execute()
{
	OnStartExecute.Broadcast();
	if (DestinationActor)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetOwner()->GetController(), DestinationActor);
	}
	else
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetOwner()->GetController(), Destination);
	}
	
}

bool UMoveCommand::CanExecute()
{
	return true;
}

void UMoveCommand::EndExecute()
{
	PathFollowingComponent->OnRequestFinished.Remove(OnPathCompleteHandle);
	OnEndExecute.Broadcast();
}

UPathFollowingComponent* UMoveCommand::GetPathFollowingComponent(AController& Controller)
{
	AAIController* AsAIController = Cast<AAIController>(&Controller);
	UPathFollowingComponent* PathFollowingComp = nullptr;

	if (AsAIController)
	{
		PathFollowingComp = AsAIController->GetPathFollowingComponent();
	}
	else
	{
		PathFollowingComp = Controller.FindComponentByClass<UPathFollowingComponent>();
		if (PathFollowingComp == nullptr)
		{
			PathFollowingComp = NewObject<UPathFollowingComponent>(&Controller);
			PathFollowingComp->RegisterComponentWithWorld(Controller.GetWorld());
			PathFollowingComp->Initialize();
		}
	}

	return PathFollowingComp;
}

void UMoveCommand::OnPathComplete(FAIRequestID RequestID, const FPathFollowingResult& PathFollowingResult)
{
	EndExecute();
}
