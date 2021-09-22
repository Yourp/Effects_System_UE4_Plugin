// Fill out your copyright notice in the Description page of Project Settings.


#include "PermanentEffect.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UPermanentEffect::UPermanentEffect()
{
    bStartPeriodicTickWhenApply = false;
}

void UPermanentEffect::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.GetPropertyName() == "BaseValue")
    {
        PeriodParameter.Initialize();
    }
}

void UPermanentEffect::OnPeriodTick()
{
    check(Caster);
    check(Owner);

    if (TickEffect)
    {
        if (TickingType == EEffectTickingType::Server)
        {
            //Owner->ApplyEffect(Caster, TickEffect);
            return;
        }

        //Owner->ApplyEffect_Implementation(Caster, TickEffect);
    }
}

void UPermanentEffect::HandleAffect(FAffectingInfo const& AffectingInfo)
{
    FFloatParameter::AffectingMethods[GetAffectingType()]->Affect(AffectingInfo);

    AffectingInfo.ChangedParameter.Recalculate();
    AffectingInfo.ChangedParameter.GetAfterChangeDelegate().Broadcast(AffectingInfo);
}

void UPermanentEffect::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UPermanentEffect, Caster);
    DOREPLIFETIME(UPermanentEffect, Owner);
}

void UPermanentEffect::OnPeriodChanged(FAffectingInfo const& AffectingInfo)
{
    if (UWorld* World = GetWorld())
    {
        FTimerManager& TimerManager = World->GetTimerManager();
        float PeriodRemaining = TimerManager.GetTimerRemaining(PeriodTimer);
        PeriodRemaining *= AffectingInfo.ChangedParameter.GetValue() / AffectingInfo.OldParameterValue;
        TimerManager.SetTimer(PeriodTimer, this, &UPermanentEffect::OnPeriodTick, PeriodParameter.GetValue(), true, PeriodRemaining);
    }
}

void UPermanentEffect::BeginPlay(UWorld* World)
{
    Super::BeginPlay(World);

    if (PeriodParameter > 0.f && (GetOwnerRole() == ROLE_Authority || TickingType == EEffectTickingType::ServerAndClient))
    {
        World->GetTimerManager().SetTimer(PeriodTimer, this, &UPermanentEffect::OnPeriodTick, PeriodParameter.GetValue(), true);
    }

    if (PeriodParameter.GetGameplayTag().IsValid())
    {
        PeriodParameter.GetAfterChangeDelegate().AddUObject(this, &UPermanentEffect::OnPeriodChanged);
    }
}

void UPermanentEffect::RegisteringAllParameters(USpellCastManagerComponent* ParamsOwner)
{
    ParamsOwner->RegisterFloatParameter(&ModifierParameter);
    ParamsOwner->RegisterFloatParameter(&PeriodParameter);
}

void UPermanentEffect::UnregisteringAllParameters(USpellCastManagerComponent* ParamsOwner)
{
    ParamsOwner->UnregisterFloatParameter(&ModifierParameter);
    ParamsOwner->UnregisterFloatParameter(&PeriodParameter);
}

void UPermanentEffect::Apply(USpellCastManagerComponent* EffectCaster, USpellCastManagerComponent* EffectTarget)
{
    UPermanentEffect* NewEffect = NewObject<UPermanentEffect>(EffectCaster, GetClass());
    NewEffect->ApplyTemporarily(EffectCaster, EffectTarget);
}

void UPermanentEffect::Remove()
{
    check(Owner);
    check(Caster);

    Owner->UnregisteringAppliedEffect(this);
    UnregisteringAllParameters(Owner);

    for (auto& Parameter : Owner->GetAllParametersWithTags())
    {
        if (Parameter->GetGameplayTag().MatchesAny(GetAffectingTag()))
        {
            FAffectingInfo AffectingInfo(Owner, Caster, *Parameter, GetModifierValue(), this, false);
            HandleAffect(AffectingInfo);
        }
    }

    Destroy();
}

void UPermanentEffect::ApplyTemporarily(USpellCastManagerComponent* EffectCaster, USpellCastManagerComponent* EffectTarget)
{
    SetCaster(EffectCaster);
    SetOwner(EffectTarget);

    Super::Apply(EffectCaster, EffectTarget);

    EffectTarget->RegisteringAppliedEffect(this);
    RegisteringAllParameters(EffectTarget);
}
