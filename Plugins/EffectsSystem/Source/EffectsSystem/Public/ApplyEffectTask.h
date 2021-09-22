// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "ApplyEffectTask.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Apply Effect"))
class EFFECTSSYSTEM_API UApplyEffectTask : public USpellTask
{
	GENERATED_BODY()
	
public:

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;

private:

    UPROPERTY(EditAnywhere, Instanced)
    class USpellEffect* Effect;
};
