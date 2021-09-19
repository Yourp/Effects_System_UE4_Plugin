// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "SettingCasterAsTarget.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API USettingCasterAsTarget : public USpellTask
{
	GENERATED_BODY()
	

public:

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;
};
