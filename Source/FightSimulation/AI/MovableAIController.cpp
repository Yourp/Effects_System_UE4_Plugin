// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableAIController.h"
#include "FightSimulation/Units/UnitCharacterBase.h"
#include "TargetFinder.h"
#include "Kismet/GameplayStatics.h"


AMovableAIController::AMovableAIController()
{

}

void AMovableAIController::BeginPlay()
{
    Super::BeginPlay();

    InitializeTargetFinder();
}

void AMovableAIController::TryToFindNewTarget()
{
    check(TargetFinder);

    TArray<AActor*> TargetsList;
    TargetFinder->FindTargets(TargetsList);

    if (TargetsList.Num() > 0)
    {
        SetTarget(TargetsList[0]);
    }
}

void AMovableAIController::SetTarget(AActor* NewTarget)
{
    Target = NewTarget;
}

void AMovableAIController::MoveToTarget(float AcceptanceRadius)
{
    MoveToActor(Target, AcceptanceRadius);
}

void AMovableAIController::InitializeTargetFinder()
{
    TargetFinder = Cast<ITargetFinder>(GetPawn());

    check(TargetFinder);
}
