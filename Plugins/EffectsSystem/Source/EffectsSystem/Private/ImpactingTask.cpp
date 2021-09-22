// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpactingTask.h"

void UImpactingTask::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    check(Target);

    float CurrentValue = ModValue;

    if (ModsTag.IsValid())
    {
        Target->ApplyAllModsTo(CurrentValue, ModsTag);
    }

    Target->Impacting(CurrentValue, AffectingTag, AffectingType);

    USpellTask::RunTaskList(NextTasks, Target, CastData);
}

void UImpactingTask::RegisteringAllFloatParameters()
{
    RegisterFloatParameter(&ModValue);
}
