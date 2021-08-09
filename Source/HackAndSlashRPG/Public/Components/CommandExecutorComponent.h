// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandExecutorComponent.generated.h"


class ABaseCharacter;
class UCommand;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASHRPG_API UCommandExecutorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCommandExecutorComponent();

	UFUNCTION(BlueprintCallable)
	void ExecuteCommand(UCommand* CommandToExecute);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Command", meta = (AllowPrivateAccess = "true"))
	UCommand* CurrentlyExecutingCommand;

	UPROPERTY()
	ABaseCharacter* CastedOwner;
};
