// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Components/CommandExecutorComponent.h"

#include "Characters/BaseCharacter.h"
#include "Commands/Command.h"

// Sets default values for this component's properties
UCommandExecutorComponent::UCommandExecutorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCommandExecutorComponent::ExecuteCommand(UCommand* CommandToExecute)
{
	CommandToExecute->TryExecute();
}


// Called when the game starts
void UCommandExecutorComponent::BeginPlay()
{
	Super::BeginPlay();

	CastedOwner = Cast<ABaseCharacter>(GetOwner());
	
}


// Called every frame
void UCommandExecutorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

