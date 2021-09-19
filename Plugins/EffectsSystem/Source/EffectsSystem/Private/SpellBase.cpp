// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"

bool USpellBase::IsTimerPending(FTimerHandle const& Timer) const
{
    UWorld* World = GetWorld();
    check(World);

    return !World->GetTimerManager().IsTimerPending(Timer);
}

void USpellBase::CooldownExpired()
{
    OnCooldownExpiredDelegate.Broadcast(this);
}

bool USpellBase::IsHasCooldown() const
{
    return !IsTimerPending(Cooldown);
}

bool USpellBase::IsInCastDelay() const
{
    return !IsTimerPending(CastDelay);
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

bool USpellBase::IsCanCast() const
{
    return true;
}

void USpellBase::SetOwner(USpellCastManagerComponent* NewOwner)
{
    Owner = NewOwner;
}


