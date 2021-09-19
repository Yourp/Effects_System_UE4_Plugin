// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCastManagerComponent.h"
#include "DurationEffect.h"
#include "FloatParameter.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "SpellBase.h"

// Sets default values for this component's properties
USpellCastManagerComponent::USpellCastManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

bool USpellCastManagerComponent::ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    for (auto& Itr : AppliedEffects)
    {
        bWroteSomething |= Channel->ReplicateSubobject(Itr, *Bunch, *RepFlags);
    }

    return bWroteSomething;
}

void USpellCastManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Called when the game starts
void USpellCastManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeFloatParameters();
}

void USpellCastManagerComponent::RegisterFloatParameter(FFloatParameter* NewParamPtr)
{
    AllFloatParameters.AddUnique(NewParamPtr);

    if (NewParamPtr->GetGameplayTag().IsValid())
    {
        AllParametersWithTags.AddUnique(NewParamPtr);
    }
}

void USpellCastManagerComponent::UnregisterFloatParameter(FFloatParameter* NewParamPtr)
{
    AllFloatParameters.RemoveSwap(NewParamPtr);
    AllParametersWithTags.RemoveSwap(NewParamPtr);
}

void USpellCastManagerComponent::ApplyEffect_Implementation(USpellCastManagerComponent* Caster, UClass* EffectClass)
{
    if (!Caster || !EffectClass)
    {
        return;
    }

    if (USpellEffect* Effect = EffectClass->GetDefaultObject<USpellEffect>())
    {
        Effect->Apply(Caster, this); 
    }
}

void USpellCastManagerComponent::RemoveEffect_Implementation(UPermanentEffect* Effect)
{
    if (Effect)
    {
        Effect->Remove();
    }
}

FFloatParameter* USpellCastManagerComponent::FindFirstParameterByTag(FGameplayTag const& Tag)
{
    for (auto& Param : AllParametersWithTags)
    {
        if (Param->GetGameplayTag().MatchesTag(Tag))
        {
            return Param;
        }
    }

    return nullptr;
}

void USpellCastManagerComponent::GetAllParametersByTag(TArray<FFloatParameter*>& ParamList, FGameplayTag const& Tag)
{
    for (auto& Param : AllParametersWithTags)
    {
        if (Param->GetGameplayTag().MatchesTag(Tag))
        {
            ParamList.Add(Param);
        }
    }
}

void USpellCastManagerComponent::GetAllParametersByTagContainer(TArray<FFloatParameter*>& ParamList, FGameplayTagContainer const& Tag)
{
    for (auto& Param : AllParametersWithTags)
    {
        if (Param->GetGameplayTag().MatchesAny(Tag))
        {
            ParamList.Add(Param);
        }
    }
}

void USpellCastManagerComponent::RegisteringAppliedEffect(UPermanentEffect* Effect)
{
    if (Effect)
    {
        AppliedEffects.Add(Effect);
    }
}

void USpellCastManagerComponent::UnregisteringAppliedEffect(UPermanentEffect* Effect)
{
    AppliedEffects.RemoveSwap(Effect);
}

void USpellCastManagerComponent::TryCastSpell(USpellBase* Spell, USpellCastManagerComponent* Target)
{
    if (Spell == nullptr || Target == nullptr)
    {
        return;
    }

    if (!IsCanCastSpell())
    {
        return;
    }

    if (!Spell->IsCanCast())
    {
        return;
    }
}

bool USpellCastManagerComponent::IsCanCastSpell() const
{
    return true;
}

TArray<FFloatParameter*> const& USpellCastManagerComponent::GetAllParametersWithTags() const
{
    return AllParametersWithTags;
}

FAffectingInfo::FAffectingInfo
(
    USpellCastManagerComponent const* NewOwner,
    USpellCastManagerComponent const* NewInitiator,
    FFloatParameter& NewChangedParameter,
    float NewModifierValue,
    USpellEffect const* NewEffect,
    bool bIsApply
)
    : Owner(NewOwner), Initiator(NewInitiator), ChangedParameter(NewChangedParameter), ModifierValue(NewModifierValue), Effect(NewEffect), bIsApplying(bIsApply)
{
    OldParameterValue = ChangedParameter.GetValue();
}








