// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellCastManagerComponent.h"
#include "SpellEffect.h"
#include "FightSimulation/SpellTaskTest.h"
#include "FightManagerComponent.generated.h"

class UAbilityBase;

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UFightManagerComponent : public USpellCastManagerComponent
{
    GENERATED_BODY()

    DECLARE_GETTERS_AND_SETTERS_OF_FLOAT_PARAMETER(Health);

    virtual void InitializeFloatParameters() override;

    

public:

    UPROPERTY(EditAnywhere)
    TSubclassOf<USpellEffect> TestEff;

    virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere)
    FFloatParameter Health;

    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<UAbilityBase>> AbilitiesDefault;

    UPROPERTY()
    TArray<UAbilityBase*> Abilities;
};
