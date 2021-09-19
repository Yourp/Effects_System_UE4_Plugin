// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellTargetMethodBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, DefaultToInstanced, editinlinenew)
class EFFECTSSYSTEM_API USpellTargetMethodBase : public UObject
{
	GENERATED_BODY()
	

public:

    virtual void ApplyEffect(class USpellEffect* Effect) {}
};
