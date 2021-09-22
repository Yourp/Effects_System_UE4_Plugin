// Fill out your copyright notice in the Description page of Project Settings.


#include "FightManagerComponent.h"
#include "AbilityBase.h"


void UFightManagerComponent::InitializeFloatParameters()
{
    INITIALIZE_FLOAT_PARAMETER(Health);
}

void UFightManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (GetOwnerRole() == ROLE_Authority)
    {
        for (auto& Itr : AbilitiesDefault)
        {
            UAbilityBase* NewAb = NewObject<UAbilityBase>(this, Itr);
            SIZE_T ssss = NewAb->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
            SIZE_T ssss2 = this->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
            SIZE_T ssss3 = this->GetOwner()->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
            Abilities.Add(NewAb);

            if (NewAb->IsCantCast())
                continue;

            NewAb->CastSpellTo(this);

            if (NewAb->IsCantCast())
                continue;
        }
    }
}
