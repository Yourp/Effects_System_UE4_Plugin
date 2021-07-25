// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"

void USpellBase::CooldownExpired()
{
    OnCooldownExpiredDelegate.Broadcast(this);
}

bool USpellBase::IsHasCooldown() const
{
    UWorld* World = GetWorld();
    check(World);

    return !World->GetTimerManager().IsTimerPending(Cooldown);
}

void USpellBase::SetCooldown(float NewCooldown)
{
    UWorld* World = GetWorld();
    check(World);

    World->GetTimerManager().SetTimer(Cooldown, this, &USpellBase::CooldownExpired, NewCooldown);
}

float USpellBase::GetCooldownTime() const
{
    UWorld* World = GetWorld();
    check(World);

    return World->GetTimerManager().GetTimerRemaining(Cooldown);
}
