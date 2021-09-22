// Fill out your copyright notice in the Description page of Project Settings.


#include "DurationEffect.h"

void UDurationEffect::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.GetPropertyName() == "BaseValue")
    {
        DurationParameter.Initialize();
    }
}

void UDurationEffect::RegisteringAllParameters(USpellCastManagerComponent* ParamsOwner)
{
    Super::RegisteringAllParameters(ParamsOwner);
    ParamsOwner->RegisterFloatParameter(&DurationParameter);
}

void UDurationEffect::UnregisteringAllParameters(USpellCastManagerComponent* ParamsOwner)
{
    Super::UnregisteringAllParameters(ParamsOwner);
    ParamsOwner->UnregisterFloatParameter(&DurationParameter);
}

void UDurationEffect::BeginPlay(UWorld* World)
{
    Super::BeginPlay(World);

    if (GetOwnerRole() == ROLE_Authority)
    {
        World->GetTimerManager().SetTimer(DurationTimer, this, &UDurationEffect::Expired, DurationParameter.GetValue(), false);
        return;
    }

    World->GetTimerManager().SetTimer(DurationTimer, DurationParameter.GetValue(), false);
}

void UDurationEffect::Expired()
{
    if (Owner)
    {
        Owner->RemoveEffect(this);
    }
}
