// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCommandExecutorComponent;
/**
 * Base rpg character
 */
UCLASS(Abstract)
class HACKANDSLASHRPG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UCommandExecutorComponent* GetCommandExecutorComponent()const { return CommandExecutor; }

private:
	UPROPERTY(VisibleAnywhere)
	UCommandExecutorComponent* CommandExecutor;
};
