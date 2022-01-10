// Fill out your copyright notice in the Description page of Project Settings.


#include "FightManagerComponent.h"
#include "AbilityBase.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"


UFightManagerComponent::UFightManagerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UFightManagerComponent::TestFunc()
{
    //TestDelegate.Broadcast(5);

    for (auto& Itr : AbilitiesDefault)
    {
        UAbilityBase* NewAb = NewObject<UAbilityBase>(this, Itr);
        Abilities.AddUnique(NewAb);
        NewAb->BeginPlay();

        SIZE_T ssss = NewAb->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
        SIZE_T ssss2 = this->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
        SIZE_T ssss3 = this->GetOwner()->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);

        FTimerHandle ttt;
        GetWorld()->GetTimerManager().SetTimer(ttt, this, &UFightManagerComponent::TestDelegateFunc, 3.f);
    }
}

void UFightManagerComponent::TestDelegateFunc()
{
    for (auto& Itr : Abilities)
    {
        if (Itr->IsCantCast())
        {
            continue;
        }

        Itr->CastTo(this);
    }
}

float UFightManagerComponent::GetHealthPct() const
{
    check (Health);
    return Health->GetEffectValue() / Health->GetLimit();
}

void UFightManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (GetOwnerRole() == ROLE_Authority)
    {
        auto InitBaseEffect = [&](USpellEffect* Effect)
        {
            if (Effect != nullptr)
            {
                Effect->BeginPlay();
                Effect->ApplyingTo(this);
            }
        };

        InitBaseEffect(Health);
        InitBaseEffect(Energy);
        InitBaseEffect(SpellPower);
        InitBaseEffect(Haste);
        InitBaseEffect(CritChance);
        InitBaseEffect(CritMultiplying);

        Abilities.Empty();
        FTimerHandle ttt;
        GetWorld()->GetTimerManager().SetTimer(ttt, this, &UFightManagerComponent::TestFunc, 10.f);
    }
}

void UFightManagerComponent::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
{
    Super::PreReplication(ChangedPropertyTracker);

}

void UFightManagerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (GetOwnerRole() != ROLE_Authority)
    {
        bool dad = false;
    }
}

void UFightManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UFightManagerComponent, Abilities);
    
}

bool UFightManagerComponent::ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    if (Abilities.Num())
    {
        for (UAbilityBase* CurrentAbility : Abilities)
        {
            bWroteSomething |= Channel->ReplicateSubobject(CurrentAbility, *Bunch, *RepFlags);
            bWroteSomething |= CurrentAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
        }
    }

    return bWroteSomething;
}

void UFightManagerComponent::EmptyTest_Implementation()
{

}

void UFightManagerComponent::OnRep_Abilities(TArray<UAbilityBase*> OldAbilities)
{

}



