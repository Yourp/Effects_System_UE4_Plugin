// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "FloatParameter.h"
#include "SpellTaskTest.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API USpellTaskTest : public USpellTask
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FFloatParameter Damage;

    UPROPERTY(EditAnywhere)
    FGameplayTag AffectedTag;

    UPROPERTY(EditAnywhere)
    FGameplayTag DamageTag;

public:

    USpellTaskTest();

    virtual void PostInitProperties() override;

    void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;
};
