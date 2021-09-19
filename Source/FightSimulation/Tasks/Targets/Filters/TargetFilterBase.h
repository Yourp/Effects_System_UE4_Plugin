// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TargetFilterBase.generated.h"

class USpellCastManagerComponent;
class USpellCastData;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, editinlinenew, DefaultToInstanced)
class FIGHTSIMULATION_API UTargetFilterBase : public UObject
{
	GENERATED_BODY()
	
public:

    virtual void FilteringTargets(TArray<AActor*>& TargetsList, USpellCastManagerComponent* Target, USpellCastData* CastData) {}
};
