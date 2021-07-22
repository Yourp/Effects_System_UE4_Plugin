// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatParameter.h"

AffectingMethod* FFloatParameter::AffectingMethods[EAffectingType::Affect_Max] =
{
    new ModifyAffect,
    new MultiplyAffect
};

void FFloatParameter::MultiplyInstant(float Rate)
{
    BaseValue *= Rate;
    Value     *= Rate;
}

void FFloatParameter::ModifyInstant(float Amount)
{
    BaseValue += Amount / Multiplying;
    Value     += Amount;
}

void FFloatParameter::MultiplyLong(FAffectingInfo const& Info)
{
    check(Info.Effect);

    Info.bIsApplying ? TotalMultiplyingEffects.Add(Info.Effect) : TotalMultiplyingEffects.RemoveSwap(Info.Effect);

    Multiplying = 1.f;

    for (auto& Itr : TotalMultiplyingEffects)
    {
        Multiplying *= Itr->GetModifierValue();
    }
}

void FFloatParameter::ModifyLong(FAffectingInfo const& Info)
{
    check(Info.Effect);

    Info.bIsApplying ? AddingEffects.Add(Info.Effect) : AddingEffects.RemoveSwap(Info.Effect);

    Adding = 0.f;

    for (auto& Itr : AddingEffects)
    {
        Adding += Itr->GetModifierValue();
    }
}

void ModifyAffect::Affect(FFloatParameter& ChangedParameter, float ModValue)
{
    ChangedParameter.ModifyInstant(ModValue);
}

void MultiplyAffect::Affect(FFloatParameter& ChangedParameter, float ModValue)
{
    ChangedParameter.MultiplyInstant(ModValue);
}

void ModifyAffect::Affect(FAffectingInfo const& Info)
{
    Info.ChangedParameter.ModifyLong(Info);
}

void MultiplyAffect::Affect(FAffectingInfo const& Info)
{
    Info.ChangedParameter.MultiplyLong(Info);
}

AffectingMethod::AffectingMethod()
{

}


