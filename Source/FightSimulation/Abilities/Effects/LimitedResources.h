// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellEffect.h"
#include "LimitedResources.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API ULimitedResources : public USpellEffect
{
	GENERATED_BODY()

public:

    FORCEINLINE FFloatParameter& GetLimit()
    {
        return Limit;
    }

    UFUNCTION()
    virtual void OnRep_Limit(FFloatParameter const& OldLimit);

    virtual void RegisterParameters(uint32 CountOfParameters) override;

    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;
	
private:

    UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Limit)
    FFloatParameter Limit;

    virtual void ClampEffectValue(float& NewEffectValue);

    virtual void CorrectionOfLimit(float& NewLimit);
};
