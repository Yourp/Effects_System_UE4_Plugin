// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellEffect.h"
#include "StaticHelper.h"
#include "ApplyEffectTask.h"
#include "Engine/ActorChannel.h"

void USpellEffect::OnPeriodChanged()
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

void USpellEffect::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(USpellEffect, EffectValue);
    DOREPLIFETIME(USpellEffect, DurationParameter);
    DOREPLIFETIME(USpellEffect, PeriodParameter);
    DOREPLIFETIME(USpellEffect, PeriodTasks);
    DOREPLIFETIME(USpellEffect, Caster);
    DOREPLIFETIME(USpellEffect, Owner);
}

bool USpellEffect::ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    if (PeriodTasks.Num())
    {
        for (USpellTask* CurrentTask : PeriodTasks)
        {
            bWroteSomething |= Channel->ReplicateSubobject(CurrentTask, *Bunch, *RepFlags);
            bWroteSomething |= CurrentTask->ReplicateSubobjects(Channel, Bunch, RepFlags);
        }
    }

    return bWroteSomething;
}

void USpellEffect::OnRep_EffectValue(FFloatParameter const& OldEffectValue)
{

}

void USpellEffect::OnRep_DurationParameter(FFloatParameter const& OldDurationParameter)
{

}

void USpellEffect::OnRep_PeriodParameter(FFloatParameter const& OldPeriodParameter)
{

}

void USpellEffect::OnRep_Caster()
{

}

void USpellEffect::OnRep_EffectOwner()
{

}

void USpellEffect::ApplyToParameter(FFloatParameter* Parameter)
{
    check(Parameter);
    *Parameter += this;
}

void USpellEffect::RemoveFromParameter(FFloatParameter* Parameter)
{
    check(Parameter);
    *Parameter -= this;
}

void USpellEffect::AddDependentFloatParameters(FFloatParameter* Param)
{
    DependentFloatParameters.AddUnique(Param);
}

void USpellEffect::RemoveDependentFloatParameters(FFloatParameter* Param)
{
    DependentFloatParameters.RemoveSwap(Param);
}

void USpellEffect::InitializeVariablesFromTask(UApplyEffectTask* ParentTask)
{
    check(ParentTask);
    check(ParentTask->GetComponentOwner());

    USpellEffect* TemplateEffect = ParentTask->GetEffect();

    SetCaster(ParentTask->GetComponentOwner());

    for (FFloatParameter* CurrentParam : AllFloatParameters)
    {
        CurrentParam->SetBaseValue(*CurrentParam);
    }

    if (ParentTask->HasNewTagNames())
    {
        auto FilterCondition = [](FFloatParameter const* Param)
        {
            return Param->GetGameplayTag().IsValid();
        };

        TArray<FFloatParameter*> FilteredParameters = AllFloatParameters.FilterByPredicate(FilterCondition);
        ParentTask->RenameParameters(FilteredParameters);
    }
}

void USpellEffect::ApplyingTo(USpellCastManagerComponent* EffectTarget)
{
    check(EffectTarget);

    SetOwner(EffectTarget);

    if (GetOwnerRole() == ROLE_Authority)
    {
        if (UWorld* World = GetWorld())
        {
            if (PeriodParameter > 0.f)
            {
                World->GetTimerManager().SetTimer(PeriodTimer, this, &USpellEffect::OnPeriodTick, PeriodParameter, true, bStartPeriodicTickWhenApply ? (0.f) : (-1.f));
            }

            if (DurationParameter > 0.f)
            {
                World->GetTimerManager().SetTimer(DurationTimer, this, &USpellEffect::DurationExpired, DurationParameter, false);
            }
        }
    }

    for (FFloatParameter* Param : GetAllFloatParameters())
    {
        GetOwner()->ApplyAllModsTo(Param);
    }

    if (GetAffectingTag().IsValid())
    {
        EffectValue.GetAfterChangeDelegate().AddUObject(this, &USpellEffect::RecalculateDependentParameters);

        for (FFloatParameter* Parameter : GetOwner()->GetAllParametersWithTags())
        {
            if (Parameter->GetGameplayTag().MatchesAny(GetAffectingTag()))
            {
                ApplyToParameter(Parameter);
            }
        }
    }

    GetOwner()->RegisteringAppliedEffect(this);
    RegisteringAllParametersToOwner(GetOwner());
}

void USpellEffect::OnPeriodTick()
{
    USpellTask::RunTaskList(PeriodTasks, GetOwner(), GetCastData());
}

void USpellEffect::RecalculateDependentParameters(float)
{
    if (DependentFloatParameters.Num())
    {
        for (FFloatParameter* CurrentParam : DependentFloatParameters)
        {
            switch (GetAffectingType())
            {
                case Affect_Add:
                {
                    CurrentParam->UpdateAddingValue();
                    break;
                }
                case Affect_Multiply:
                {
                    CurrentParam->UpdateMultiplyingValue();
                    break;
                }
            }

            CurrentParam->Recalculate();
        }
    }
}

void USpellEffect::DurationExpired()
{
    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &USpellEffect::Remove);
}

void USpellEffect::RegisterParameters(uint32 CountOfParameters)
{
    AllFloatParameters.Empty(CountOfParameters);

    AllFloatParameters.Add(&EffectValue);
    AllFloatParameters.Add(&PeriodParameter  );
    AllFloatParameters.Add(&DurationParameter);
}

void USpellEffect::InitializeParameters()
{
    for (FFloatParameter* CurrentParam : AllFloatParameters)
    {
        CurrentParam->Initialize();
    }
}

void USpellEffect::BeginPlay()
{
    Super::BeginPlay();

    if (GetOwnerRole() == ROLE_Authority)
    {
        for (USpellTask* Task : PeriodTasks)
        {
            if (!Task->HasBegunPlay())
            {
                Task->BeginPlay();
            }
        }
    }

    RegisterParameters(3);
    InitializeParameters();
}

void USpellEffect::RegisteringAllParametersToOwner(USpellCastManagerComponent* ParamsOwner)
{
    for (FFloatParameter* CurrentParam : AllFloatParameters)
    {
        ParamsOwner->RegisterFloatParameter(CurrentParam);
    }
}

void USpellEffect::UnregisteringAllParametersFromOwner(USpellCastManagerComponent* ParamsOwner)
{
    for (FFloatParameter* CurrentParam : AllFloatParameters)
    {
        ParamsOwner->UnregisterFloatParameter(CurrentParam);
    }
}

void USpellEffect::Remove()
{
    check(Owner);
    check(Caster);

    if (GetAffectingTag().IsValid())
    {
        while (DependentFloatParameters.Num())
        {
            FFloatParameter* Parameter = *DependentFloatParameters.GetData();

            if (Parameter->GetGameplayTag().MatchesAny(GetAffectingTag()))
            {
                RemoveFromParameter(Parameter);
            }
        }
    }

    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
    Owner->UnregisteringAppliedEffect(this);
    UnregisteringAllParametersFromOwner(Owner);
    Destroy();
}



