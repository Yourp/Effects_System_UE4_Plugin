// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellCastData.generated.h"

class USpellCastManagerComponent;

/**
 * 
 */
UCLASS(BlueprintType)
class EFFECTSSYSTEM_API USpellCastData : public UObject
{
	GENERATED_BODY()
	
public:

    FORCEINLINE USpellCastManagerComponent* GetCaster() const
    {
        return Caster;
    }

    AActor* GetCasterActor() const;

    FORCEINLINE void SetCaster(USpellCastManagerComponent* NewCaster)
    {
        Caster = NewCaster;
    }

    ~USpellCastData();

private:

    UPROPERTY()
    USpellCastManagerComponent* Caster;
};
