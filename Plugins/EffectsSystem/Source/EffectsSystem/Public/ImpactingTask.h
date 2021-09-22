// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "FloatParameter.h"
#include "ImpactingTask.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Impact"))
class EFFECTSSYSTEM_API UImpactingTask : public USpellTask
{
	GENERATED_BODY()
	
public:

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;

    virtual void RegisteringAllFloatParameters() override;

private:

    UPROPERTY(EditAnywhere)
    FFloatParameter ModValue;

    UPROPERTY(EditAnywhere)
    FGameplayTagContainer AffectingTag;

    UPROPERTY(EditAnywhere)
    FGameplayTag ModsTag;

    UPROPERTY(EditAnywhere)
    TEnumAsByte<EAffectingType> AffectingType;
};
