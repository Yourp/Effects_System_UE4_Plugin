// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellCastManagerComponent.h"
#include "SpellEffect.h"
#include "FightManagerComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UFightManagerComponent : public USpellCastManagerComponent
{
    GENERATED_BODY()

    virtual void InitializeFloatParameters() override;

public:

    UPROPERTY(EditAnywhere)
    TSubclassOf<USpellEffect> TestEff;

    virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere)
    FFloatParameter Health;

public:

    FORCEINLINE float GetHealth() const
    {
        return Health.GetValue();
    }

    FORCEINLINE float GetHealthBase() const
    {
        return Health.GetBaseValue();
    }

    FORCEINLINE float GetHealthAdding() const
    {
        return Health.GetAdding();
    }

    FORCEINLINE float GetHealthMultiplying() const
    {
        return Health.GetMultiplying();
    }

    FORCEINLINE const FGameplayTag& GetHealthGameplayTag() const
    {
        return Health.GetGameplayTag();
    }

//     FORCEINLINE FFloatParameter::FAfterChange& GetHealthChangeDelegate()
//     {
//         return Health.GetAfterChangeDelegate();
//     }

    FORCEINLINE void SetHealth(float NewHealthValue)
    {
        Health.SetValue(NewHealthValue);
    }

    FORCEINLINE void SetHealthBase(float NewHealthValue)
    {
        Health.SetBaseValue(NewHealthValue);
    }

//     FORCEINLINE void MultiplyHealthInstant(float Rate)
//     {
//         Health.MultiplyInstant(Rate);
//     }
// 
//     FORCEINLINE void ModifyHealthInstant(float Amount)
//     {
//         Health.ModifyInstant(Amount);
//     }
};
