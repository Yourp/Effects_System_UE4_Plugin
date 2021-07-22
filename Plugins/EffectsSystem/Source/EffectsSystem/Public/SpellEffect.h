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
UCLASS()
class EFFECTSSYSTEM_API USpellEffect : public UReplicatedObject
{
	GENERATED_BODY()
	
public:

    FORCEINLINE virtual bool HasDuration() const { return false; }

    FORCEINLINE virtual bool IsInstant() const { return true; }

    FORCEINLINE virtual bool IsPermanent() const { return false; }

    FORCEINLINE uint8 GetAffectingType() const { return AffectingType; }

    FORCEINLINE float GetModifierValue() const { return Modifier.GetValue(); }

    FORCEINLINE FGameplayTagContainer const& GetAffectingTag() const { return AffectingTag; }

    virtual void HandleAffect(FAffectingInfo const& AffectingInfo);

    virtual void Apply(USpellCastManagerComponent* EffectCaster, USpellCastManagerComponent* EffectTarget);

protected:

    UPROPERTY(EditAnywhere, Category = "Modifier")
    FFloatParameter Modifier;

    UPROPERTY(EditAnywhere, Category = "Modifier")
    FGameplayTagContainer AffectingTag;

    UPROPERTY(EditAnywhere, Category = "Modifier")
    TEnumAsByte<EAffectingType> AffectingType;

    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

private:

};
