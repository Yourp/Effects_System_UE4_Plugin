// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetFilterBase.h"
#include "TargetFilterByDistance.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UTargetFilterByDistance : public UTargetFilterBase
{
	GENERATED_BODY()
	
public:

    virtual void FilteringTargets(TArray<AActor*>& TargetsList, USpellCastManagerComponent* Target, USpellCastData*) override;

private:

    UPROPERTY(EditAnywhere)
    float Radius;

    UPROPERTY(EditAnywhere)
    uint8 bRemoveOutsideCircle : 1;
};
