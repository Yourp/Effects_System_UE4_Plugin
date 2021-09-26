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
    DECLARE_GETTERS_AND_SETTERS_OF_FLOAT_PARAMETER(SpellPower);
    DECLARE_GETTERS_AND_SETTERS_OF_FLOAT_PARAMETER(Haste);

    virtual void InitializeFloatParameters() override;

    

public:

    DECLARE_MULTICAST_DELEGATE_OneParam(FTestDelegateSSS, float)

    FTestDelegateSSS TestDelegate;

    void TestFunc();
    void TestDelegateFunc(float ddd);

    UPROPERTY(EditAnywhere)
    TSubclassOf<USpellEffect> TestEff;

    virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere)
    FFloatParameter Health;

    UPROPERTY(EditAnywhere)
    FFloatParameter SpellPower;

    UPROPERTY(EditAnywhere)
    FFloatParameter Haste;

    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<UAbilityBase>> AbilitiesDefault;

    UPROPERTY()
    TArray<UAbilityBase*> Abilities;
};
