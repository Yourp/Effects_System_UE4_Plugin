// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellEffect.h"
#include "StaticHelper.h"

void USpellEffect::OnPeriodChanged(FAffectingInfo const& AffectingInfo)
{
    if (UWorld* World = GetWorld())
    {
//         FTimerManager& TimerManager = World->GetTimerManager();
//         float PeriodRemaining = TimerManager.GetTimerRemaining(PeriodTimer);
//         PeriodRemaining *= AffectingInfo.ChangedParameter.GetValue() / AffectingInfo.OldParameterValue;
//         TimerManager.SetTimer(PeriodTimer, this, &USpellEffect::OnPeriodTick, PeriodParameter.GetValue(), true, PeriodRemaining);
    }
}

void USpellEffect::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

//     if (PropertyChangedEvent.GetPropertyName() == "BaseValue")
//     {
//         ModifierParameter.Initialize();
//         PeriodParameter  .Initialize();
//         DurationParameter.Initialize();
//     }
}

void USpellEffect::AddToParameter(FFloatParameter* Parameter)
{
    check(Parameter);
    *Parameter += this;
}

void USpellEffect::RemoveFromParameter(FFloatParameter* Parameter)
{
    check(Parameter);
    *Parameter -= this;
}

void USpellEffect::Apply(USpellCastManagerComponent* EffectTarget)
{
    if (GetOwnerRole() == ROLE_Authority)
    {
        check(EffectTarget);

        SetOwner(EffectTarget);

        if (UWorld* World = GetWorld())
        {
            if (PeriodParameter > 0.f)
            {
                World->GetTimerManager().SetTimer(PeriodTimer, this, &USpellEffect::OnPeriodTick, PeriodParameter, true);
            }

            if (DurationParameter > 0.f)
            {
                World->GetTimerManager().SetTimer(DurationTimer, this, &USpellEffect::DurationExpired, DurationParameter, false);
            }
        }

        GetOwner()->RegisteringAppliedEffect(this);
        RegisteringAllParameters(GetOwner());

        for (FFloatParameter* Parameter : GetOwner()->GetAllParametersWithTags())
        {
            if (Parameter->GetGameplayTag().MatchesAny(GetAffectingTag()))
            {
                AddToParameter(Parameter);
            }
        }
    }
}

void USpellEffect::OnPeriodTick()
{

}

void USpellEffect::DurationExpired()
{

}

void USpellEffect::BeginPlay(UWorld* World)
{
    Super::BeginPlay(World);

    Caster = FStaticHelper::FindFirstOuterByClass<USpellCastManagerComponent>(GetOuter());

    check(Caster);
}

void USpellEffect::RegisteringAllParameters(USpellCastManagerComponent* ParamsOwner)
{
    ParamsOwner->RegisterFloatParameter(&ModifierParameter);
    ParamsOwner->RegisterFloatParameter(&PeriodParameter);
    ParamsOwner->RegisterFloatParameter(&DurationParameter);
}

void USpellEffect::UnregisteringAllParameters(USpellCastManagerComponent* ParamsOwner)
{
    ParamsOwner->UnregisterFloatParameter(&ModifierParameter);
    ParamsOwner->UnregisterFloatParameter(&PeriodParameter);
    ParamsOwner->UnregisterFloatParameter(&DurationParameter);
}

void USpellEffect::Remove()
{
    check(Owner);
    check(Caster);

    Owner->UnregisteringAppliedEffect(this);
    UnregisteringAllParameters(Owner);

    for (auto& Parameter : Owner->GetAllParametersWithTags())
    {
        if (Parameter->GetGameplayTag().MatchesAny(GetAffectingTag()))
        {
            RemoveFromParameter(Parameter);
        }
    }

    Destroy();
}

void USpellEffect::ApplyTemporarily(USpellCastManagerComponent* EffectCaster, USpellCastManagerComponent* EffectTarget)
{

}

