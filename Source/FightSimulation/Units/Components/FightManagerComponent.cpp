// Fill out your copyright notice in the Description page of Project Settings.


#include "FightManagerComponent.h"

void UFightManagerComponent::InitializeFloatParameters()
{
    INITIALIZE_FLOAT_PARAMETER(Health);
}

void UFightManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    ApplyEffect(this, TestEff);
    
}
