// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellEffect.h"
#include "PermanentEffect.generated.h"

UENUM()
enum class EEffectTickingType : uint8
{
    Server,
    ServerAndClient
};

/**
 * 
 */
UCLASS()
class EFFECTSSYSTEM_API UPermanentEffect : public USpellEffect
{
	GENERATED_BODY()
	
public:

    UPermanentEffect();

    FORCEINLINE virtual bool HasDuration() const { return false; }

    FORCEINLINE virtual bool IsInstant() const { return false; }

    FORCEINLINE virtual bool IsPermanent() const { return true; }

    FORCEINLINE USpellCastManagerComponent* GetCaster() const { return Caster; }
    FORCEINLINE USpellCastManagerComponent* GetOwner()  const { return Owner;  }

    FORCEINLINE void SetCaster  ( USpellCastManagerComponent* NewCaster ) { Caster = NewCaster; }
    FORCEINLINE void SetOwner   ( USpellCastManagerComponent* NewOwner  ) { Owner  = NewOwner;  }

    virtual void OnPeriodTick();

    virtual void HandleAffect(FAffectingInfo const& AffectingInfo) override;

    virtual void RegisteringAllParameters  (USpellCastManagerComponent* ParamsOwner);
    virtual void UnregisteringAllParameters(USpellCastManagerComponent* ParamsOwner);

    virtual void Apply(USpellCastManagerComponent* EffectCaster, USpellCastManagerComponent* EffectTarget) override;
    virtual void Remove();

    virtual void ApplyTemporarily(USpellCastManagerComponent* EffectCaster, USpellCastManagerComponent* EffectTarget);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:

    UPROPERTY(EditAnywhere, Category = "Period")
    FFloatParameter Period;

    UPROPERTY(EditAnywhere, Category = "Period")
    TSubclassOf<USpellEffect> TickEffect;

    UPROPERTY(EditAnywhere, Category = "Period")
    uint8 bStartPeriodicTickWhenApply : 1;

    UPROPERTY(EditAnywhere, Category = "Period")
    EEffectTickingType TickingType;

    FTimerHandle PeriodTimer;

    UPROPERTY(Replicated)
    USpellCastManagerComponent* Caster;

    UPROPERTY(Replicated)
    USpellCastManagerComponent* Owner;

    virtual void OnPeriodChanged(FAffectingInfo const& AffectingInfo);

    virtual void BeginPlay(UWorld* World) override;
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

private:

    
};
