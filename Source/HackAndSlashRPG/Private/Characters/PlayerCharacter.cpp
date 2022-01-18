// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AttributesComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StatsComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void APlayerCharacter::ConfigureAttributeComponent()
{
	AttributesComponent = CreateDefaultSubobject<UAttributesComponent>("Attributes");

	AttributesComponent->OnStrengthChange.AddDynamic(this, &APlayerCharacter::OnStrengthChange);
	AttributesComponent->OnAgilityChange.AddDynamic(this, &APlayerCharacter::APlayerCharacter::OnAgilityChange);
	AttributesComponent->OnIntelligenceChange.AddDynamic(this, &APlayerCharacter::APlayerCharacter::OnIntelligenceChange);
	AttributesComponent->OnVitalityChange.AddDynamic(this, &APlayerCharacter::APlayerCharacter::OnVitalityChange);
}

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

	ConfigureAttributeComponent();

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

}

FAttributes APlayerCharacter::GetAttributes() const
{
	return AttributesComponent->GetAttributes();
}

void APlayerCharacter::OnStrengthChange(int32 Change)
{
	const float DmgPerStrength = GetAttributes().DmgPerStrength;
	GetStatsComponent()->AddDamageMultiplier(DmgPerStrength * Change);
}

void APlayerCharacter::OnAgilityChange(int32 Change)
{
	const float CooldownReductionPerAgility = GetAttributes().CooldownReductionPerAgility;
	GetStatsComponent()->AddAttackCooldown(CooldownReductionPerAgility * Change);
}

void APlayerCharacter::OnIntelligenceChange(int32 Change)
{
	const float MpPerIntelligence = GetAttributes().MpPerIntelligence;
	GetStatsComponent()->AddMana(MpPerIntelligence * Change);
}

void APlayerCharacter::OnVitalityChange(int32 Change)
{
	const float HpPerVitality = GetAttributes().HpPerVitality;
	GetStatsComponent()->AddHealth(HpPerVitality * Change);
}
