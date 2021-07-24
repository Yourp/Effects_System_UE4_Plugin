// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellCastManagerComponent.h"
#include "SpellEffect.h"
#include "FightManagerComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UFightManagerComponent : public USpellCastManagerComponent
{
    GENERATED_BODY()

    virtual void InitializeFloatParameters() override;

    DECLARE_FLOAT_PARAMETER_FULL(Health);

public:

    UPROPERTY(EditAnywhere)
    TSubclassOf<USpellEffect> TestEff;

    virtual void BeginPlay() override;

    
};
