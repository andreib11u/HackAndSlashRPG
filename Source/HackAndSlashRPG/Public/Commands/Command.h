// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Command.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEndExecute);
DECLARE_MULTICAST_DELEGATE(FOnStartExecute);

class ABaseCharacter;
/**
 * Make owner do actions
 */
UCLASS(Abstract)
class HACKANDSLASHRPG_API UCommand : public UObject
{
	GENERATED_BODY()
public:
	
	/**
	 * Execute a command despite restrictions
	 */
	UFUNCTION(BlueprintCallable)
	virtual void Execute();

	/**
	 * restrict use of a command
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool CanExecute();

	/**
	 * if a command can be interrupted
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool CanInterrupt();

	/**
	 * Execute a command if CanExecute() returned true
	 */
	UFUNCTION(BlueprintCallable)
	virtual void TryExecute();

	/**
	 * always call when a command ends
	 */
	UFUNCTION(BlueprintCallable)
	virtual void EndExecute();

	FOnEndExecute OnEndExecute;
	FOnStartExecute OnStartExecute;
	
	ABaseCharacter* GetOwner()const { return Owner; }
	void SetOwner(ABaseCharacter* OwnerToSet) { Owner = OwnerToSet; }
protected:
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character", meta = (AllowPrivateAccess = "true"))
	ABaseCharacter* Owner;
};
