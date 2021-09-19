// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetFinder.h"
#include "Caster.h"
#include "SpellCastManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Filters/TargetFilterBase.h"
#include "Sorters/TargetSorterBase.h"
#include "SpellCastData.h"

void UTargetFinder::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    TArray<AActor*> Targets;
    
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UCaster::StaticClass(), Targets);

    if (bExcludeCaster)
    {
        Targets.RemoveSwap(CastData->GetCasterActor());
    }

    if (bExcludeCurrentTarget)
    {
        Targets.RemoveSwap(Target->GetOwner());
    }

    FilteringTargets(Targets, Target, CastData);
    SortingTargets  (Targets, Target, CastData);


    if (MaxTargets > 0 && Targets.Num() > MaxTargets)
    {
        Targets.SetNum(MaxTargets);
    }

    if (Targets.Num() > 0)
    {
        for (auto& CurrentTarget : Targets)
        {
            if (ICaster* SpellTarget = Cast<ICaster>(CurrentTarget))
            {
                RunTaskList(NextTasks, SpellTarget->GetSpellCastManagerComponent(), CastData);
            }
        }
    }
    
}

void UTargetFinder::FilteringTargets(TArray<AActor*>& TargetsList, USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    if (FiltersList.Num() > 0)
    {
        for (auto& Filter : FiltersList)
        {
            Filter->FilteringTargets(TargetsList, Target, CastData);
        }
    }
}

void UTargetFinder::SortingTargets(TArray<AActor*>& TargetsList, USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    if (TargetsList.Num() > 1)
    {
        if (UTargetSorterBase* SorterPtr = Sorter.GetDefaultObject())
        {
            SorterPtr->SortingTargets(TargetsList, Target, CastData);
        }
    }
}

