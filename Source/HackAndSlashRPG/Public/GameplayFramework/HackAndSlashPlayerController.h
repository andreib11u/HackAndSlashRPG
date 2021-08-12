// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HackAndSlashPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API AHackAndSlashPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void SetupInputComponent() override;
	
	void SetDestination();
protected:
	virtual void BeginPlay() override;
};
