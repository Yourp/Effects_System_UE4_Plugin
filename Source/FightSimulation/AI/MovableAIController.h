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

    virtual void InitializeTargetFinder();

protected:

    virtual void MoveToTarget(float AcceptanceRadius = -1);
    virtual void TryToFindNewTarget();
    virtual void SetTarget(AActor* NewTarget);

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
