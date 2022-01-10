// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTask.h"
#include "SpellCastManagerComponent.h"
#include "StaticHelper.h"
#include "AbilityBase.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

void USpellTask::UnregisteringAllFloatParameters()
{
    if (GetComponentOwner() != nullptr)
    {
        while (AllFloatParameters.Num())
        {
            FFloatParameter* Param = *AllFloatParameters.GetData();
            GetComponentOwner()->UnregisterFloatParameter(Param);
            AllFloatParameters.RemoveSwap(Param);
        }
    }
}

void USpellTask::RegisteringAllParametersForOwner()
{
    for (FFloatParameter* Param : AllFloatParameters)
    {
        Param->Initialize();
        ComponentOwner->ApplyAllModsTo(Param);
        ComponentOwner->RegisterFloatParameter(Param);
    }
}

void USpellTask::OnRep_ActorOwner()
{

}

void USpellTask::OnRep_ComponentOwner()
{

}

void USpellTask::OnRep_AbilityOwner()
{

}

USpellTask::~USpellTask()
{

}

void USpellTask::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    /** Handle task. */

    RunTaskList(NextTasks, Target, CastData);
}

void USpellTask::BeginPlay()
{
    Super::BeginPlay();

    if (GetOwnerRole() == ROLE_Authority)
    {
        for (USpellTask* Task : NextTasks)
        {
            if (!Task->HasBegunPlay())
            {
                Task->BeginPlay();
            }
        }

        ComponentOwner  = FStaticHelper::FindFirstOuterByClass<USpellCastManagerComponent>(this);
        AbilityOwner    = FStaticHelper::FindFirstOuterByClass<UAbilityBase              >(this);
        ActorOwner      = FStaticHelper::FindFirstOuterByClass<AActor                    >(this);

        check(ComponentOwner);

        FillInParameters();
        RegisteringAllParametersForOwner();

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

bool USpellTask::ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    if (NextTasks.Num())
    {
        for (USpellTask* CurrentTask : NextTasks)
        {
            bWroteSomething |= Channel->ReplicateSubobject(CurrentTask, *Bunch, *RepFlags);
            bWroteSomething |= CurrentTask->ReplicateSubobjects(Channel, Bunch, RepFlags);
        }
    }

    return bWroteSomething;
}

void USpellTask::RunTaskList(TArray<USpellTask*> const& TaskList, USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    for (USpellTask* CurrentTask : TaskList)
    {
        if (CurrentTask != nullptr)
        {
            CurrentTask->Run(Target, CastData);
        }
    }
}

void USpellTask::AddFloatParameter(FFloatParameter* NewParam)
{
    AllFloatParameters.AddUnique(NewParam);
}

void USpellTask::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(USpellTask,     ActorOwner);
    DOREPLIFETIME(USpellTask, ComponentOwner);
    DOREPLIFETIME(USpellTask,   AbilityOwner);
}
