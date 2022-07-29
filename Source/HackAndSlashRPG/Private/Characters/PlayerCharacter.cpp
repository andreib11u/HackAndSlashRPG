// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatsAndAttributes/Attributes.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));

	SpringArm->TargetArmLength = 800.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	
	TopDownCamera->SetupAttachment(SpringArm);

	auto CharacterMovementComponent = Cast<UCharacterMovementComponent>(ACharacter::GetMovementComponent());
	bUseControllerRotationYaw = false;
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->RotationRate = FRotator(0.f, 1000.f, 0.f);

	// Not response to player's own cursor
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1/*MouseCursor*/, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1/*MouseCursor*/, ECollisionResponse::ECR_Ignore);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::PostInitProperties()
{
	Super::PostInitProperties();

	Attributes = NewObject<UAttributes>();
	Attributes->Init(this);
}

void APlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
