// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatParameter.h"
#include "SpellEffect.h"

void FFloatParameter::operator-=(USpellEffect const* Effect)
{
    check(Effect);

    if (AddingEffects.RemoveSwap(Effect))
    {
        UpdateAddingValue();
    }

    if (TotalMultiplyingEffects.RemoveSwap(Effect))
    {
        UpdateAddingValue();
    }

    float OldValue = GetValue();

    Recalculate();

    if (OldValue != GetValue())
    {
        AfterChangeDelegate.Broadcast(GetValue());
    }
}

void FFloatParameter::operator+=(USpellEffect const* Effect)
{
    check(Effect);

    switch (Effect->GetAffectingType())
    {
        case Affect_Add:
        {
            AddingEffects.Add(Effect);
            UpdateAddingValue();
            break;
        }
        case Affect_Multiply:
        {
            TotalMultiplyingEffects.Add(Effect);
            UpdateMultiplyingValue();
            break;
        }
    }

    float OldValue = GetValue();

    Recalculate();

    if (OldValue != GetValue())
    {
        AfterChangeDelegate.Broadcast(GetValue());
    }
}

void FFloatParameter::operator*=(float Val)
{
    BaseValue *= Val;
    Value     *= Val;

    AfterChangeDelegate.Broadcast(GetValue());
}

void FFloatParameter::operator+=(float Val)
{
    BaseValue += Val / Multiplying;
    Value     += Val;

    AfterChangeDelegate.Broadcast(GetValue());
}

void FFloatParameter::UpdateMultiplyingValue()
{
    Multiplying = 1.f;

    for (auto& Itr : TotalMultiplyingEffects)
    {
        Multiplying *= Itr->GetModifierValue();
    }
}

void FFloatParameter::UpdateAddingValue()
{
    Adding = 0.f;

    for (auto& Itr : AddingEffects)
    {
        Adding += Itr->GetModifierValue();
    }
}

void FFloatParameter::SetValue(float NewValue)
{
    if (Value != NewValue)
    {
        Value = NewValue;
        AfterChangeDelegate.Broadcast(GetValue());
    }
}

float FFloatParameter::Calculate(float Base, float Add, float Multiply)
{
    return (Base + Add) * Multiply;
}






