// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterAbility.h"
#include "FightSimulation/Tasks/Delayed/Cooldown.h"

bool UFighterAbility::IsHasCooldown() const
{
    return CooldownTaskPtr ? CooldownTaskPtr->IsHasCooldown() : false;
}

void UFighterAbility::SetCooldown(float NewCooldown)
{
    if (CooldownTaskPtr != nullptr)
    {
        CooldownTaskPtr->SetCooldown(NewCooldown);
    }
}

float UFighterAbility::GetCooldownTime() const
{
    return CooldownTaskPtr ? CooldownTaskPtr->GetCooldownTime() : 0;
}

void UFighterAbility::SetCooldownClass(UCooldown* NewCooldownClass)
{
    CooldownTaskPtr = NewCooldownClass;
}
