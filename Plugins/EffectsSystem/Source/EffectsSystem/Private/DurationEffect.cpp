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

void UDurationEffect::AddAllParametersTo(TArray<FFloatParameter*>& Params)
{
    Super::AddAllParametersTo(Params);

    if (Duration.GetGameplayTag().IsValid())
    {
        Params.Add(&Duration);
    }
}

void UDurationEffect::RemoveParametersFrom(TArray<FFloatParameter*>& Params)
{
    Super::RemoveParametersFrom(Params);
    Params.RemoveSwap(&Duration);
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
