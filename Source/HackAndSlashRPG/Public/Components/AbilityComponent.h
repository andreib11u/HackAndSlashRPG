// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


class UAbility;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASHRPG_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilityComponent();

	UFUNCTION(BlueprintCallable)
	void ExecuteAbility(UAbility* Ability);

	/**
	 * Set ability's owner to run to the target and then Execute()
	 * @param Ability - An ability to execute after reaching the target
	 */
	UFUNCTION(BlueprintCallable)
	void QueueAbility(UAbility* Ability);

	UFUNCTION(BlueprintCallable)
	void UnQueueCurrentAbility();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAbility* CurrentAbility;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bQueuedAbility;
};
