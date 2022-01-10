// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpactingTask.h"
#include "Net/UnrealNetwork.h"

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

void UImpactingTask::FillInParameters()
{
    AddFloatParameter(&ModValue);
}

void UImpactingTask::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UImpactingTask, ModValue);
}

void UImpactingTask::OnRep_ModValue(FFloatParameter const& OldValue)
{

}
