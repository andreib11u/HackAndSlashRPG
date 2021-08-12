// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Commands/MoveAndAttackCommand.h"
#include "Characters/BaseCharacter.h"

void UMoveAndAttackCommand::Init(ABaseCharacter* OwnerToSet, ABaseCharacter* TargetToSet)
{
	SetOwner(OwnerToSet);
	Target = TargetToSet;

	PathFollowingComponent = GetPathFollowingComponent(*GetOwner()->GetController());

	if (PathFollowingComponent)
	{
		OnPathCompleteHandle = PathFollowingComponent->OnRequestFinished.AddUObject(this, &UMoveAndAttackCommand::OnPathComplete);
	}
}

void UMoveAndAttackCommand::Execute()
{
	OnStartExecute.Broadcast();
}

void UMoveAndAttackCommand::Attack(ABaseCharacter* AttackTarget)
{
	
}

void UMoveAndAttackCommand::OnPathComplete(FAIRequestID RequestID, const FPathFollowingResult& PathFollowingResult)
{
	Attack(Target);
}
