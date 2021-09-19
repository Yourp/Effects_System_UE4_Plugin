// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTaskTest.h"
#include "Kismet\GameplayStatics.h"
#include "TestCastData.h"
#include "Caster.h"
#include "SpellCastManagerComponent.h"

USpellTaskTest::USpellTaskTest()
{

}

void USpellTaskTest::PostInitProperties()
{
    Super::PostInitProperties();
}

void USpellTaskTest::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{

}

void USpellTaskTest::AddParam(float Val)
{
    Param += Val;
}
