// Fill out your copyright notice in the Description page of Project Settings.


#include "Cooldown.h"
#include "AbilityBase.h"
#include "EffectsSystemHelpMacros.h"
#include "FightSimulation/Abilities/FighterAbility.h"

UCooldown::UCooldown() : Super()
{
    CastCheckDelegate.BindUObject(this, &UCooldown::IsHasCooldown);
}

void UCooldown::CooldownExpired()
{
    OnCooldownExpiredDelegate.Broadcast(this);
}

void UCooldown::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    USpellTask::RunTaskList(NextTasks, Target, CastData);
    SetCooldown(RecoveryTime);
}

uint64 UCooldown::IsHasCooldown() const
{
    UWorld* World = GetWorld();
    check(World);

    return World->GetTimerManager().TimerExists(CooldownTimer);
}

void UCooldown::SetCooldown(float NewCooldown)
{
    UWorld* World = GetWorld();
    check(World);

    World->GetTimerManager().SetTimer(CooldownTimer, this, &UCooldown::CooldownExpired, NewCooldown);
}

float UCooldown::GetCooldownTime() const
{
    UWorld* World = GetWorld();
    check(World);

    return World->GetTimerManager().GetTimerRemaining(CooldownTimer);
}

void UCooldown::PostInitProperties()
{
    Super::PostInitProperties();

    if (UFighterAbility* Ability = Cast<UFighterAbility>(GetAbilityOwner()))
    {
        Ability->SetCooldownClass(this);
    }
}

void UCooldown::FillInParameters()
{
    AddFloatParameter(&RecoveryTime);
}
