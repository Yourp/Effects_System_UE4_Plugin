// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "FighterAbility.generated.h"

class UCooldown;

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UFighterAbility : public UAbilityBase
{
	GENERATED_BODY()
	

public:

    bool IsHasCooldown() const;

    void  SetCooldown(float NewCooldown);

    float GetCooldownTime() const;

    void SetCooldownClass(UCooldown* NewCooldownClass);

private:

    UPROPERTY()
    UCooldown* CooldownTaskPtr;
};
