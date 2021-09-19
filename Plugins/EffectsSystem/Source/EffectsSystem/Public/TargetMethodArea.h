// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTargetMethodBase.h"
#include "TargetMethodArea.generated.h"

/**
 * 
 */
UCLASS()
class EFFECTSSYSTEM_API UTargetMethodArea : public USpellTargetMethodBase
{
	GENERATED_BODY()
	
private:

    UPROPERTY(EditAnywhere)
    FFloatParameter Radius;

public: 

    UTargetMethodArea();
};
