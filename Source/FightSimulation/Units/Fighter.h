// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fighter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFighter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIGHTSIMULATION_API IFighter
{
	GENERATED_BODY()

public:

    virtual bool IsCanAttack() const = 0;

    virtual void Attack(AActor* Target) = 0;

    virtual float GetAttackRange() const = 0;
};
