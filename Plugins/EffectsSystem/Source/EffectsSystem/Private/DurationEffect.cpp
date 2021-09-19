// Fill out your copyright notice in the Description page of Project Settings.


#include "DurationEffect.h"

void UDurationEffect::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.GetPropertyName() == "BaseValue")
    {
        Duration.Initialize();
    }
}

void UDurationEffect::RegisteringAllParameters(USpellCastManagerComponent* ParamsOwner)
{
    Super::RegisteringAllParameters(ParamsOwner);
    ParamsOwner->RegisterFloatParameter(&Duration);
}

void UDurationEffect::UnregisteringAllParameters(USpellCastManagerComponent* ParamsOwner)
{
    Super::UnregisteringAllParameters(ParamsOwner);
    ParamsOwner->UnregisterFloatParameter(&Duration);
}

void UDurationEffect::BeginPlay(UWorld* World)
{
    Super::BeginPlay(World);

    if (GetOwnerRole() == ROLE_Authority)
    {
        World->GetTimerManager().SetTimer(DurationTimer, this, &UDurationEffect::Expired, Duration.GetValue(), false);
        return;
    }

    World->GetTimerManager().SetTimer(DurationTimer, Duration.GetValue(), false);
}

void UDurationEffect::Expired()
{
    if (Owner)
    {
        Owner->RemoveEffect(this);
    }
}
