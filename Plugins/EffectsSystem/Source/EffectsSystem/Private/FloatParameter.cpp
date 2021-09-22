// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatParameter.h"

AffectingMethod* FFloatParameter::AffectingMethods[EAffectingType::Affect_Max] =
{
    new ModifyAffect,
    new MultiplyAffect
};

void FFloatParameter::operator*=(FAffectingInfo const& Info)
{
    check(Info.Effect);

    Info.bIsApplying ? TotalMultiplyingEffects.Add(Info.Effect) : TotalMultiplyingEffects.RemoveSwap(Info.Effect);

    Multiplying = 1.f;

    for (auto& Itr : TotalMultiplyingEffects)
    {
        Multiplying *= Itr->GetModifierValue();
    }
}

void FFloatParameter::operator+=(FAffectingInfo const& Info)
{
    check(Info.Effect);

    Info.bIsApplying ? AddingEffects.Add(Info.Effect) : AddingEffects.RemoveSwap(Info.Effect);

    Adding = 0.f;

    for (auto& Itr : AddingEffects)
    {
        Adding += Itr->GetModifierValue();
    }
}

void FFloatParameter::operator*=(float Val)
{
    BaseValue *= Val;
    Value     *= Val;
}

void FFloatParameter::operator+=(float Val)
{
    BaseValue += Val / Multiplying;
    Value     += Val;
}

float FFloatParameter::Calculate(float Base, float Add, float Multiply)
{
    return (Base + Add) * Multiply;
}

void ModifyAffect::Affect(FFloatParameter& ChangedParameter, float ModValue)
{
    ChangedParameter += ModValue;
}

void MultiplyAffect::Affect(FFloatParameter& ChangedParameter, float ModValue)
{
    ChangedParameter *= ModValue;
}

void ModifyAffect::Affect(FAffectingInfo const& Info)
{
    Info.ChangedParameter += Info;
}

void MultiplyAffect::Affect(FAffectingInfo const& Info)
{
    Info.ChangedParameter *= Info;
}




