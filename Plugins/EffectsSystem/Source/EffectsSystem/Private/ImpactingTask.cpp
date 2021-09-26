// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpactingTask.h"

void UImpactingTask::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    check(Target);

    float CurrentValue = GetCalculatedValue(Target, CastData);

    AffectToTarget(Target, CurrentValue);

    USpellTask::RunTaskList(NextTasks, Target, CastData);
}

float UImpactingTask::GetCalculatedValue(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    float CurrentValue = ModValue;

    if (TagForTargetMods.IsValid())
    {
        Target->ApplyAllModsTo(CurrentValue, TagForTargetMods);
    }

    return CurrentValue;
}

void UImpactingTask::AffectToTarget(USpellCastManagerComponent* Target, float Amount)
{
    Target->Impacting(Amount, AffectingTag, AffectingType);
}

void UImpactingTask::RegisteringAllFloatParameters()
{
    RegisterFloatParameter(&ModValue);
}
