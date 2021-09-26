// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "SpellCastManagerComponent.h"
#include "FloatParameter.h"
#include "SpellEffect.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, DefaultToInstanced)
class EFFECTSSYSTEM_API USpellEffect : public UReplicatedObject
{
	GENERATED_BODY()
	
public:

    FORCEINLINE uint8 GetAffectingType() const { return AffectingType; }

    FORCEINLINE float GetModifierValue() const { return ModifierParameter; }

    FORCEINLINE FGameplayTagContainer const& GetAffectingTag() const { return AffectingTag; }

    virtual void Apply(USpellCastManagerComponent* EffectTarget);

    virtual void RegisteringAllParameters  (USpellCastManagerComponent* ParamsOwner);
    virtual void UnregisteringAllParameters(USpellCastManagerComponent* ParamsOwner);

    virtual void Remove();

    virtual void ApplyTemporarily(USpellCastManagerComponent* EffectCaster, USpellCastManagerComponent* EffectTarget);

    FORCEINLINE USpellCastManagerComponent* GetCaster() const { return Caster; }
    FORCEINLINE USpellCastManagerComponent* GetOwner()  const { return Owner;  }

    FORCEINLINE void SetCaster  ( USpellCastManagerComponent* NewCaster ) { Caster = NewCaster; }
    FORCEINLINE void SetOwner   ( USpellCastManagerComponent* NewOwner  ) { Owner  = NewOwner;  }

protected:

    UPROPERTY(EditAnywhere)
    FFloatParameter ModifierParameter;

    UPROPERTY(EditAnywhere)
    FGameplayTagContainer AffectingTag;

    UPROPERTY(EditAnywhere)
    TEnumAsByte<EAffectingType> AffectingType;

    UPROPERTY(EditAnywhere, Category = "Period")
    FFloatParameter PeriodParameter;

    UPROPERTY(EditAnywhere, Category = "Period")
    uint8 bStartPeriodicTickWhenApply : 1;

    FTimerHandle PeriodTimer;

    UPROPERTY(EditAnywhere)
    FFloatParameter DurationParameter;

    FTimerHandle DurationTimer;

    UPROPERTY()
    USpellCastManagerComponent* Caster;

    UPROPERTY()
    USpellCastManagerComponent* Owner;

    virtual void AddToParameter     (FFloatParameter* Parameter);
    virtual void RemoveFromParameter(FFloatParameter* Parameter);

    virtual void OnPeriodChanged(FAffectingInfo const& AffectingInfo);

    virtual void OnPeriodTick();

    virtual void DurationExpired();

    virtual void BeginPlay(UWorld* World) override;

    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

private:

};
