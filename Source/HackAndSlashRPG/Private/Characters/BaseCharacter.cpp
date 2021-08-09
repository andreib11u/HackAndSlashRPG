// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/BaseCharacter.h"
#include "HackAndSlashRPG/Public/Components/CommandExecutorComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CommandExecutor = CreateDefaultSubobject<UCommandExecutorComponent>(TEXT("CommandExecutor"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

