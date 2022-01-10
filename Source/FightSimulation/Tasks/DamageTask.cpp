// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTask.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/FightPlayerController.h"

void UDamageTask::AffectToTarget(USpellCastManagerComponent* Target, float Amount)
{
    bool bIsCrit = false;

    if (CritChance && CritBonusDamage && FMath::RandRange(0.f, 100.f) <= CritChance)
    {
        Amount += Amount * CritBonusDamage;
        bIsCrit = true;
    }

    APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (AFightPlayerController* FightPlayerController = Cast<AFightPlayerController>(PController))
    {
        FightPlayerController->AddCombatLogData(GetComponentOwner(), Target, this, FMath::Abs(Amount), bIsCrit);
    }

    Super::AffectToTarget(Target, Amount);
}

void UDamageTask::FillInParameters()
{
    Super::FillInParameters();

    AddFloatParameter(&CritChance);
    AddFloatParameter(&CritBonusDamage);
}


