// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Targets/TargetFinder.h"
#include "Fighter.h"
#include "UnitCharacterBase.generated.h"

class UFightManagerComponent;

UCLASS()
class FIGHTSIMULATION_API AUnitCharacterBase : public ACharacter, public ITargetFinder, public IFighter
{
	GENERATED_BODY()

private:

    UPROPERTY(EditAnywhere)
    UFightManagerComponent* SpellCastManagerComponent;

public:
	// Sets default values for this character's properties
	AUnitCharacterBase();

    virtual void FindTargets(TArray<AActor*>& Targets) override;

    virtual bool IsCanAttack() const override;

    virtual void Attack(AActor* Target) override;

    virtual float GetAttackRange() const override;
};
