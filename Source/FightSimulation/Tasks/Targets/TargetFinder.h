// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "TargetFinder.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UTargetFinder : public USpellTask
{
    GENERATED_BODY()

public:

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;

    virtual void FilteringTargets(TArray<AActor*>& TargetsList, USpellCastManagerComponent* Target, USpellCastData* CastData);
    virtual void SortingTargets  (TArray<AActor*>& TargetsList, USpellCastManagerComponent* Target, USpellCastData* CastData);

private:

    UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
    int32 MaxTargets;

    UPROPERTY(EditAnywhere)
    uint8 bExcludeCaster : 1;

    UPROPERTY(EditAnywhere)
    uint8 bExcludeCurrentTarget : 1;

    UPROPERTY(EditAnywhere, Instanced)
    TArray<class UTargetFilterBase*> FiltersList;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UTargetSorterBase> Sorter;

protected:

};
