// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovableAIController.h"
#include "FighterAIController.generated.h"

class IFighter;

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API AFighterAIController : public AMovableAIController
{
    GENERATED_BODY()

private:

    IFighter* Fighter;


protected:


public:


    virtual void BeginPlay() override;
};
