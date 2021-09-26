// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "SpellCastManagerComponent.h"
#include "SpellCastData.h"

void UAbilityBase::CastSpellTo(USpellCastManagerComponent* Target)
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

USpellCastData* UAbilityBase::CreateSpellCastData()
{
    if (CastData != nullptr)
    {
        return NewObject<USpellCastData>(this, CastData);
    }

    return NewObject<USpellCastData>(this, USpellCastData::StaticClass());
}

