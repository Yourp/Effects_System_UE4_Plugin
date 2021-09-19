// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetFilterByDistance.h"
#include "SpellCastManagerComponent.h"

void UTargetFilterByDistance::FilteringTargets(TArray<AActor*>& TargetsList, USpellCastManagerComponent* Target, USpellCastData*)
{
    AActor const* TargetOwnerActor = Target->GetOwner();

    TargetsList.RemoveAllSwap([=](AActor const* CurrentActor)
    {
        return (TargetOwnerActor->GetDistanceTo(CurrentActor) > Radius) == bRemoveOutsideCircle;
    });
}
