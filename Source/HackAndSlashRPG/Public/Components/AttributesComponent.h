// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EAttribute : uint8
{
	Strength UMETA(DisplayName = "Strength"),
	Agility UMETA(DisplayName = "Agility"),
	Intelligence UMETA(DisplayName = "Intelligence"),
	Vitality UMETA(DisplayName = "Vitality")
};

USTRUCT(BlueprintType)
struct FAttributes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Strength = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Agility = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Intelligence = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Vitality = 10;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HpPerVitality = 11.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MpPerIntelligence = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DmgPerStrength = 0.08f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownReductionPerAgility = 0.01f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStrengthChange, int32, StrengthChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAgilityChange, int32, AgilityChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIntelligenceChange, int32, IntelligenceChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVitalityChange, int32, VitalityChange);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASHRPG_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributesComponent();

	FAttributes GetAttributes()const { return Attributes; }

	/**
	 * Cannot spend more than there is in PointsToSpend
	 * @param Attribute - The attribute to spend points on
	 * @param Points - How many points to spend. If more points passed, than there is - spends all available points
	 */
	UFUNCTION(BlueprintCallable)
	void SpendPointsOnAttribute(const EAttribute Attribute, const int32 Points);
	
	/**
	 * Add attribute points without spending them
	 * @param Attribute - The attribute to add
	 * @param Points - How many points to add
	 */
	UFUNCTION(BlueprintCallable)
	void AddAttribute(const EAttribute Attribute, const int32 Points);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnStrengthChange OnStrengthChange;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAgilityChange OnAgilityChange;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnIntelligenceChange OnIntelligenceChange;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnVitalityChange OnVitalityChange;
	
protected:
	virtual void BeginPlay() override;
private:
	int32& GetAttributeReference(const EAttribute Attribute);
	void BroadcastMessage(const EAttribute Attribute, const int32 Points);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	FAttributes Attributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	FAttributes InitialAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points", meta = (AllowPrivateAccess = "true"))
	int32 PointsToSpend;
		
};
