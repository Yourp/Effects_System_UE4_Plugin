// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ImpactingTask.h"
#include "DamageTask.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UDamageTask : public UImpactingTask
{
	GENERATED_BODY()
	

public:

    virtual void AffectToTarget(USpellCastManagerComponent* Target, float Amount) override;

    virtual void FillInParameters() override;

private:

    UPROPERTY(EditAnywhere)
    FFloatParameter CritChance;

    UPROPERTY(EditAnywhere)
    FFloatParameter CritBonusDamage;

protected:

};
