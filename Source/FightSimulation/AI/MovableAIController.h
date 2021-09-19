// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MovableAIController.generated.h"

class ITargetFinder;

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API AMovableAIController : public AAIController
{
	GENERATED_BODY()

public:

    AMovableAIController();
	
private:


    ITargetFinder* TargetFinder;

    AActor* Target;


protected:


public:

    virtual void BeginPlay() override;

    FORCEINLINE AActor* GetTarget() const
    {
        return Target;
    }

    FORCEINLINE ITargetFinder const* GetTargetFinder() const
    {
        return TargetFinder;
    }
};
