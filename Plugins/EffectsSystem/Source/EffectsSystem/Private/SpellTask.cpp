// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTask.h"
#include "SpellCastManagerComponent.h"
#include "StaticHelper.h"
#include "AbilityBase.h"

void USpellTask::InitializeAllFloatParameters()
{
    if (AllFloatParameters.Num() > 0)
    {
        for (auto& Param : AllFloatParameters)
        {
            Param->Initialize();
        }
    }
}

void USpellTask::UnregisteringAllFloatParameters()
{
    if (GetOwner() != nullptr)
    {
        if (AllFloatParameters.Num() > 0)
        {
            for (auto& Param : AllFloatParameters)
            {
                GetOwner()->UnregisterFloatParameter(Param);
            }
        }
    }
}

USpellTask::~USpellTask()
{

}

void USpellTask::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    /** Handle task. */

    RunTaskList(NextTasks, Target, CastData);
}

void USpellTask::PostInitProperties()
{
    Super::PostInitProperties();

    if (GetWorld())
    {
        Owner        = FStaticHelper::FindFirstOuterByClass<USpellCastManagerComponent>(this);
        AbilityOwner = FStaticHelper::FindFirstOuterByClass<UAbilityBase              >(this);
        ActorOwner   = FStaticHelper::FindFirstOuterByClass<AActor                    >(this);

        check(Owner);

        RegisteringAllFloatParameters();
        InitializeAllFloatParameters();

        if (GetAbilityOwner() != nullptr && CastCheckDelegate.IsBound())
        {
            GetAbilityOwner()->AddCheckCastDelegate(&CastCheckDelegate);
        }
    }
}

void USpellTask::BeginDestroy()
{
    Super::BeginDestroy();

    if (GetAbilityOwner() != nullptr)
    {
        GetAbilityOwner()->RemoveCheckCastDelegate(&CastCheckDelegate);
    }

    UnregisteringAllFloatParameters();
}

void USpellTask::RunTaskList(TArray<USpellTask*> const& TaskList, USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    if (TaskList.Num() > 0)
    {
        for (auto& CurrentTask : TaskList)
        {
            if (CurrentTask != nullptr)
            {
                CurrentTask->Run(Target, CastData);
            }
        }
    }
}

void USpellTask::RegisterFloatParameter(FFloatParameter* NewParam)
{
    AllFloatParameters.AddUnique(NewParam);
    Owner->RegisterFloatParameter(NewParam);
}
