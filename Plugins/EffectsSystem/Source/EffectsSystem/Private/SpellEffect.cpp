// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellEffect.h"

void USpellEffect::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.GetPropertyName() == "BaseValue")
    {
        ModifierParameter.Initialize();
    }
}

void USpellEffect::HandleAffect(FAffectingInfo const& AffectingInfo)
{
    FFloatParameter& Param = AffectingInfo.ChangedParameter;

    if (ModifierParameter.GetValue() && Param.GetMultiplying() > 0.f)
    {
        FFloatParameter::AffectingMethods[GetAffectingType()]->Affect(AffectingInfo.ChangedParameter, ModifierParameter.GetValue());
        Param.GetAfterChangeDelegate().Broadcast(AffectingInfo);
    }
}

void USpellEffect::Apply(USpellCastManagerComponent* EffectCaster, USpellCastManagerComponent* EffectTarget)
{
    for (auto& Parameter : EffectTarget->GetAllParametersWithTags())
    {
        if (Parameter->GetGameplayTag().MatchesAny(GetAffectingTag()))
        {
            FAffectingInfo AffectingInfo(EffectTarget, EffectCaster, *Parameter, GetModifierValue(), this, true);
            HandleAffect(AffectingInfo);
        }
    }
}


