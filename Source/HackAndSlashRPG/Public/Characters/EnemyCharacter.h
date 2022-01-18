// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASHRPG_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

private:
	/* Shows when player points mouse cursor on enemy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* TargetDecal;

	UFUNCTION()
	void OnMouseEnter(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnMouseLeft(UPrimitiveComponent* TouchedComponent);
};

