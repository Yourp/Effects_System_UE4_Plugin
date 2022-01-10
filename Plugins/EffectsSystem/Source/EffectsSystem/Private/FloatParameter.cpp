// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatParameter.h"
#include "SpellEffect.h"

void FFloatParameter::operator-=(USpellEffect* Effect)
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

    Effect->RemoveDependentFloatParameters(this);
    Recalculate();
}

void FFloatParameter::operator+=(USpellEffect* Effect)
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

    Effect->AddDependentFloatParameters(this);
    Recalculate();
}

void FFloatParameter::operator*=(float Val)
{
    float OldValue = Value;

    BaseValue *= Val;
    Value     *= Val;

    if (OldValue != Value)
    {
        OnChangeDelegate.ExecuteIfBound(Value);
        AfterChangeDelegate.Broadcast(Value);
    }
}

void FFloatParameter::operator+=(float Val)
{
    float OldValue = Value;

    BaseValue += Val / Multiplying;
    Value     += Val;

    if (OldValue != Value)
    {
        OnChangeDelegate.ExecuteIfBound(Value);
        AfterChangeDelegate.Broadcast(Value);
    }
}

void FFloatParameter::UpdateMultiplyingValue()
{
    Multiplying = 1.f;

    for (USpellEffect const* Itr : TotalMultiplyingEffects)
    {
        Multiplying *= Itr->GetModifierValue();
    }
}

void FFloatParameter::UpdateAddingValue()
{
    Adding = 0.f;

    for (USpellEffect const* Itr : AddingEffects)
    {
        Adding += Itr->GetModifierValue();
    }
}

void FFloatParameter::Recalculate()
{
    float OldValue = Value;

    Value = Calculate(BaseValue, Adding, Multiplying);

    if (OldValue != Value)
    {
        OnChangeDelegate.ExecuteIfBound(Value);
        AfterChangeDelegate.Broadcast(Value);
    }
}

void FFloatParameter::ClearListOfMods(TArray<USpellEffect*>& List)
{
    while (List.Num())
    {
        USpellEffect* CurrentEffect = *List.GetData();

        if (CurrentEffect != nullptr)
        {
            CurrentEffect->RemoveDependentFloatParameters(this);
        }

        List.RemoveSwap(CurrentEffect);
    }
}

void FFloatParameter::Initialize()
{
    if (!bIsInitialized)
    {
        Value = BaseValue;
        bIsInitialized = true;
    }
}

void FFloatParameter::SetValue(float NewValue)
{
    if (Value != NewValue)
    {
        Value = NewValue;

        OnChangeDelegate.ExecuteIfBound(Value);
        AfterChangeDelegate.Broadcast(Value);
    }
}

void FFloatParameter::RemoveAllMods()
{
    ClearListOfMods(AddingEffects);
    ClearListOfMods(TotalMultiplyingEffects);

    Multiplying = 1.f;
    Adding = 0.f;

    Recalculate();
}

float FFloatParameter::Calculate(float Base, float Add, float Multiply)
{
    return (Base + Add) * Multiply;
}

void FFloatParameter::operator=(float Val)
{
    SetValue(Val);
}

