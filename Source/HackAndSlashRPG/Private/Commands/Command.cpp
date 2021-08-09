// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Commands/Command.h"

void UCommand::Execute()
{
	unimplemented();
}

bool UCommand::CanExecute()
{
	unimplemented();
	return false;
}

bool UCommand::CanInterrupt()
{
	unimplemented();
	return false;
}

void UCommand::TryExecute()
{
	if (CanExecute())
	{
		Execute();
	}
}

void UCommand::EndExecute()
{
	unimplemented();
}
