// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplyEffectTask.h"
#include "SpellEffect.h"
#include "Engine/ActorChannel.h"

void UApplyEffectTask::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    if (USpellEffect* NewEffect = CreateEffect())
    {
        NewEffect->SetCastData(CastData);
        NewEffect->ApplyingTo(Target);

        USpellTask::RunTaskList(NextTasks, Target, CastData);
    }
}

void UApplyEffectTask::RenameParameters(TArray<FFloatParameter*> const& Params)
{
    if (HasNewTagNames())
    {
        if (Params.Num() > 0)
        {
            for (FFloatParameter* CurrentParam : Params)
            {
                for (FTagRenamerData const& RenamerData : ListOfNewTagsName)
                {
                    if (CurrentParam->GetGameplayTag() != RenamerData.NewName && CurrentParam->GetGameplayTag().MatchesAny(RenamerData.Names))
                    {
                        CurrentParam->SetGameplayTag(RenamerData.NewName);
                    }
                }
            }
        }
    }
}

bool UApplyEffectTask::ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    if (Effect != nullptr)
    {
        bWroteSomething |= Channel->ReplicateSubobject(Effect, *Bunch, *RepFlags);
        bWroteSomething |= Effect->ReplicateSubobjects(Channel, Bunch, RepFlags);
    }

    return bWroteSomething;
}

void UApplyEffectTask::BeginPlay()
{
    if (Effect != nullptr && GetOwnerRole() == ROLE_Authority)
    {
        if (!Effect->HasBegunPlay())
        {
            Effect->BeginPlay();
        }
    }

    Super::BeginPlay();
}

USpellEffect* UApplyEffectTask::CreateEffect()
{
    if (Effect == nullptr)
    {
        /** TODO: Warning msg. */
        return nullptr;
    }

    USpellEffect* NewEffect = NewObject<USpellEffect>(this, NAME_None, EObjectFlags::RF_NoFlags, Effect);
    NewEffect->BeginPlay();
    NewEffect->InitializeVariablesFromTask(this);

    return NewEffect;
}

void UApplyEffectTask::FillInParameters()
{
    if (Effect != nullptr)
    {
        if (Effect->GetAllFloatParameters().Num())
        {
            for (FFloatParameter* CurrentParam : Effect->GetAllFloatParameters())
            {
                AddFloatParameter(CurrentParam);
            }
        }
    }
}
