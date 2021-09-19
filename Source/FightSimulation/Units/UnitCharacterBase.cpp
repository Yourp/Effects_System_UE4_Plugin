// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitCharacterBase.h"
#include "Components/FightManagerComponent.h"

// Sets default values
AUnitCharacterBase::AUnitCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SpellCastManagerComponent = CreateDefaultSubobject<UFightManagerComponent>("FightManagerComponent");
}

USpellCastManagerComponent* AUnitCharacterBase::GetSpellCastManagerComponent() const
{
    return SpellCastManagerComponent;
}





