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
    FFloatParameter Param;

public:

    USpellTaskTest();

    virtual void PostInitProperties() override;

    void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;

    void AddParam(float Val);
};
