// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCastManagerComponent.h"
#include "FloatParameter.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "SpellEffect.h"

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

    if (AppliedEffects.Num())
    {
        for (USpellEffect* CurrentEffect : AppliedEffects)
        {
            bWroteSomething |= Channel->ReplicateSubobject(CurrentEffect, *Bunch, *RepFlags);
            bWroteSomething |= CurrentEffect->ReplicateSubobjects(Channel, Bunch, RepFlags);
        }
    }

    return bWroteSomething;
}

void USpellCastManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(USpellCastManagerComponent, AppliedEffects);
}

void USpellCastManagerComponent::OnRep_AppliedEffects(TArray<USpellEffect*> Old)
{

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
    NewParamPtr->RemoveAllMods();

    AllFloatParameters.RemoveSwap(NewParamPtr);
    AllParametersWithTags.RemoveSwap(NewParamPtr);
}

void USpellCastManagerComponent::ApplyEffect_Implementation(USpellCastManagerComponent* Caster, USpellEffect* Effect)
{
    if (!Caster || !Effect)
    {
        return;
    }

    Effect->ApplyingTo(this); 
}

void USpellCastManagerComponent::RemoveEffect_Implementation(USpellEffect* Effect)
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

void USpellCastManagerComponent::Impacting(float Amount, FGameplayTagContainer const& ImpactTag, EAffectingType Type)
{
    for (FFloatParameter* CurrentParameter : AllParametersWithTags)
    {
        if (CurrentParameter->GetGameplayTag().MatchesAny(ImpactTag))
        {
            switch (Type)
            {
                case Affect_Add:
                {
                    *CurrentParameter += Amount;
                    break;
                }
                case Affect_Multiply:
                {
                    *CurrentParameter *= Amount;
                    break;
                }
            }
        }
    }
}

void USpellCastManagerComponent::ApplyAllModsTo(float& Amount, FGameplayTag const& AmountName)
{
    Amount += GetModifierFor   (AmountName);
    Amount *= GetMultiplayerFor(AmountName);
}

void USpellCastManagerComponent::ApplyAllModsTo(FFloatParameter* Param)
{
    if (Param->GetGameplayTag().IsValid())
    {
        for (USpellEffect* Effect : GetAppliedEffects())
        {
            if (!Effect->GetAffectingTag().IsEmpty() && Param->GetGameplayTag().MatchesAny(Effect->GetAffectingTag()))
            {
                Effect->ApplyToParameter(Param);
            }
        }
    }
}

float USpellCastManagerComponent::GetModifierFor(FGameplayTag const& Tag) const
{
    float Modifier = 0;

    for (USpellEffect const* Effect : AppliedEffects)
    {
        if (Effect->GetAffectingType() == EAffectingType::Affect_Add && Tag.MatchesAny(Effect->GetAffectingTag()))
        {
            Modifier += Effect->GetModifierValue();
        }
    }

    return Modifier;
}

float USpellCastManagerComponent::GetMultiplayerFor(FGameplayTag const& Tag) const
{
    float Multiplayer = 1.f;

    for (USpellEffect const* Effect : AppliedEffects)
    {
        if (Effect->GetAffectingType() == EAffectingType::Affect_Multiply && Tag.MatchesAny(Effect->GetAffectingTag()))
        {
            Multiplayer *= Effect->GetModifierValue();
        }
    }

    return Multiplayer;
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

void USpellCastManagerComponent::RegisteringAppliedEffect(USpellEffect* Effect)
{
    if (Effect)
    {
        AppliedEffects.AddUnique(Effect);
    }
}

void USpellCastManagerComponent::UnregisteringAppliedEffect(USpellEffect* Effect)
{
    AppliedEffects.RemoveSwap(Effect);
}

TArray<FFloatParameter*> const& USpellCastManagerComponent::GetAllParametersWithTags() const
{
    return AllParametersWithTags;
}

TArray<USpellEffect*> const& USpellCastManagerComponent::GetAppliedEffects() const
{
    return AppliedEffects;
}









