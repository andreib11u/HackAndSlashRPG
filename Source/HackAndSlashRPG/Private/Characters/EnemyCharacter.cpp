// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1/*MouseCursor*/, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCapsuleSize(50.f, 88.f);
	GetCapsuleComponent()->OnBeginCursorOver.AddDynamic(this, &AEnemyCharacter::OnMouseEnter);
	GetCapsuleComponent()->OnEndCursorOver.AddDynamic(this, &AEnemyCharacter::OnMouseLeft);

	TargetDecal = CreateDefaultSubobject<UDecalComponent>("TargetDecal");
	TargetDecal->DecalSize = FVector(16.f, 32.f, 32.f);
	TargetDecal->SetVisibility(false);
	TargetDecal->SetupAttachment(RootComponent);
	TargetDecal->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	TargetDecal->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}

void AEnemyCharacter::OnMouseEnter(UPrimitiveComponent* TouchedComponent)
{
	TargetDecal->SetVisibility(true);
}

void AEnemyCharacter::OnMouseLeft(UPrimitiveComponent* TouchedComponent)
{
	TargetDecal->SetVisibility(false);
}
