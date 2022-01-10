// Fill out your copyright notice in the Description page of Project Settings.


#include "LimitedResources.h"
#include "Net/UnrealNetwork.h"

void ULimitedResources::OnRep_Limit(FFloatParameter const& OldLimit)
{

}

void ULimitedResources::RegisterParameters(uint32 CountOfParameters)
{
    Super::RegisterParameters(CountOfParameters + 1);

    AllFloatParameters.Add(&Limit);
}

void ULimitedResources::BeginPlay()
{
    Super::BeginPlay();

    GetLimit()      .GetOnChangeDelegate().BindUObject(this, &ULimitedResources::CorrectionOfLimit);
    GetEffectValue().GetOnChangeDelegate().BindUObject(this, &ULimitedResources::ClampEffectValue);
}

void ULimitedResources::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ULimitedResources, Limit);
}

void ULimitedResources::ClampEffectValue(float& NewEffectValue)
{
    NewEffectValue = FMath::Clamp<float>(NewEffectValue, 0.f, Limit);
}

void ULimitedResources::CorrectionOfLimit(float& NewLimit)
{
    if (NewLimit < 1.f)
    {
        NewLimit = 1.f;
    }
}
