// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Caster.h"
#include "UnitCharacterBase.generated.h"

class UFightManagerComponent;

UCLASS()
class FIGHTSIMULATION_API AUnitCharacterBase : public ACharacter, public ICaster
{
	GENERATED_BODY()

private:

    UPROPERTY(EditAnywhere)
    UFightManagerComponent* SpellCastManagerComponent;

public:
	// Sets default values for this character's properties
	AUnitCharacterBase();

    virtual USpellCastManagerComponent* GetSpellCastManagerComponent() const;
};
