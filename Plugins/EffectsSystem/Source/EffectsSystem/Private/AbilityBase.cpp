// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "SpellCastManagerComponent.h"
#include "SpellCastData.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

void UAbilityBase::CastTo(USpellCastManagerComponent* Target)
{
    USpellCastManagerComponent* Caster = Cast<USpellCastManagerComponent>(GetOuter());
    check(Caster);

    USpellCastData* NewData = CreateSpellCastData();
    NewData->SetCaster(Caster);

    USpellTask::RunTaskList(SpellTasks, Target, NewData);
}

void UAbilityBase::AddCheckCastDelegate(FAbilityCastCheck* CheckDelegate)
{
    if (CheckDelegate->IsBound())
    {
        CastChecks.AddUnique(CheckDelegate);
    }
}

void UAbilityBase::RemoveCheckCastDelegate(FAbilityCastCheck* CheckDelegate)
{
    CastChecks.RemoveSwap(CheckDelegate);
}

uint64 UAbilityBase::IsCantCast() const
{
    for (FAbilityCastCheck const* Checker : CastChecks)
    {
        if (Checker->IsBound())
        {
            /** TODO: Warning */
            uint64 Reason = Checker->Execute();

            if (Reason != 0)
            {
                return Reason;
            }
        }
    }
    return 0;
}

void UAbilityBase::BeginPlay()
{
    Super::BeginPlay();

    if (GetOwnerRole() == ROLE_Authority)
    {
        for (USpellTask* Task : SpellTasks)
        {
            if (!Task->HasBegunPlay())
            {
                Task->BeginPlay();
            }
        }
    }
}

void UAbilityBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //DOREPLIFETIME(UAbilityBase, SpellTasks);

}

bool UAbilityBase::ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    if (SpellTasks.Num())
    {
        for (USpellTask* CurrentTask : SpellTasks)
        {
            bWroteSomething |= Channel->ReplicateSubobject(CurrentTask, *Bunch, *RepFlags);
            bWroteSomething |= CurrentTask->ReplicateSubobjects(Channel, Bunch, RepFlags);
        }
    }

    return bWroteSomething;
}

USpellCastData* UAbilityBase::CreateSpellCastData()
{
    if (CastData != nullptr)
    {
        return NewObject<USpellCastData>(this, CastData);
    }

    return NewObject<USpellCastData>(this, USpellCastData::StaticClass());
}

