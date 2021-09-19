// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCastData.h"
#include "SpellCastManagerComponent.h"

AActor* USpellCastData::GetCasterActor() const
{
    if (Caster != nullptr)
    {
        return Caster->GetOwner();
    }

    return nullptr;
}

USpellCastData::~USpellCastData()
{

}
