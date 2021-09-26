// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTaskTest.h"
#include "Kismet\GameplayStatics.h"
#include "TestCastData.h"
#include "Caster.h"
#include "Units/Components/FightManagerComponent.h"

USpellTaskTest::USpellTaskTest()
{

}

void USpellTaskTest::PostInitProperties()
{
    Super::PostInitProperties();
}

void USpellTaskTest::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    UFightManagerComponent* ttt = Cast<UFightManagerComponent>(CastData->GetCaster());

    ttt->TestDelegate.AddUFunction(this, "TestDelegateFunct");
    ttt->TestDelegate.AddUFunction(this, "TestDelegateFunct");
    ttt->TestDelegate.AddUFunction(this, "TestDelegateFunct");
    ttt->TestDelegate.AddUFunction(this, "TestDelegateFunct");
    ttt->TestDelegate.AddUFunction(this, "TestDelegateFunct");

    FFloatParameter NewDamage;
    NewDamage.SetGameplayTag(DamageTag);
}

void USpellTaskTest::TestDelegateFunct(float ddd)
{

}

