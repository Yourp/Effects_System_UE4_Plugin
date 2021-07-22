// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterAIController.h"
#include "../Units/Fighter.h"


void AFighterAIController::InitializeFighter()
{
    Fighter = Cast<IFighter>(GetPawn());

    check(Fighter);
}

void AFighterAIController::BeginPlay()
{
    Super::BeginPlay();

    InitializeFighter();
}

void AFighterAIController::AttackTarget()
{
    check(Fighter);

    Fighter->Attack(GetTarget());
}

void AFighterAIController::TryAttackTarget()
{
    check(Fighter)

    if (!GetTarget())
    {
        return;
    }

    if (!CheckRangeConditions())
    {
        MoveToTarget(Fighter->GetAttackRange());
        return;
    }

    if (CheckAttackConditions())
    {
        AttackTarget();
    }
}

bool AFighterAIController::CheckAttackConditions() const
{
    check(Fighter);

    return Fighter->IsCanAttack();
}

bool AFighterAIController::CheckRangeConditions() const
{
    check(GetPawn());

    float CurrentDistance = FVector::Dist(GetPawn()->GetActorLocation(), GetTarget()->GetActorLocation());

    return CurrentDistance <= Fighter->GetAttackRange();
}

void AFighterAIController::SetTarget(AActor* NewTarget)
{
    Super::SetTarget(NewTarget);

    TryAttackTarget();
}
