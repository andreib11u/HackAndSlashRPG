// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Animation/AttackLandNotify.h"

#include "Characters/BaseCharacter.h"

void UAttackLandNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	auto Owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (Owner)
	{
		Owner->SetLockedInAnimation(false);
		Owner->OnAttackLand.Broadcast();
	}
}
