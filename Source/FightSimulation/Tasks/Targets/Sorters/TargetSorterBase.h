// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TargetSorterBase.generated.h"

class USpellCastManagerComponent;
class USpellCastData;

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class FIGHTSIMULATION_API UTargetSorterBase : public UObject
{
	GENERATED_BODY()
	
public:

    virtual void SortingTargets(TArray<AActor*>& TargetsList, USpellCastManagerComponent* Target, USpellCastData* CastData) {}
};
