// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "SpellCastManagerComponent.h"
#include "FloatParameter.h"
#include "SpellEffect.generated.h"

class USpellCastData;

/**
 * 
 */
UCLASS(editinlinenew, DefaultToInstanced)
class EFFECTSSYSTEM_API USpellEffect : public UReplicatedObject
{
	GENERATED_BODY()
	
public:

    FORCEINLINE uint8 GetAffectingType() const { return AffectingType; }

    FORCEINLINE float GetModifierValue() const { return EffectValue; }

    FORCEINLINE FGameplayTagContainer const& GetAffectingTag() const { return AffectingTag; }

    FORCEINLINE TArray<FFloatParameter*> const& GetAllFloatParameters() const
    {
        return AllFloatParameters;
    }

    FORCEINLINE TArray<FFloatParameter*> const& GetDependentFloatParameters() const
    {
        return DependentFloatParameters;
    }

    void AddDependentFloatParameters   (FFloatParameter* Param);
    void RemoveDependentFloatParameters(FFloatParameter* Param);

    virtual void InitializeVariablesFromTask(class UApplyEffectTask* ParentTask);

    UFUNCTION(/*NetMulticast, Unreliable*/)
    virtual void ApplyingTo(USpellCastManagerComponent* EffectTarget);

    virtual void RegisteringAllParametersToOwner    (USpellCastManagerComponent* ParamsOwner);
    virtual void UnregisteringAllParametersFromOwner(USpellCastManagerComponent* ParamsOwner);

    virtual void Remove();

    FORCEINLINE USpellCastManagerComponent* GetCaster() const { return Caster; }
    FORCEINLINE USpellCastManagerComponent* GetOwner()  const { return Owner;  }

    FORCEINLINE void SetCaster  ( USpellCastManagerComponent* NewCaster ) { Caster = NewCaster; }
    FORCEINLINE void SetOwner   ( USpellCastManagerComponent* NewOwner  ) { Owner  = NewOwner;  }

    FORCEINLINE void SetCastData(USpellCastData* NewCastData)
    {
        CastData = NewCastData;
    }

    FORCEINLINE USpellCastData* GetCastData() const
    {
        return CastData;
    }

    FORCEINLINE FFloatParameter& GetEffectValue()
    {
        return EffectValue;
    }

    FORCEINLINE FFloatParameter& GetDurationParameter()
    {
        return DurationParameter;
    }

    FORCEINLINE FFloatParameter& GetPeriodParameter()
    {
        return PeriodParameter;
    }

    virtual void ApplyToParameter   (FFloatParameter* Parameter);
    virtual void RemoveFromParameter(FFloatParameter* Parameter);

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

    virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

    virtual void BeginPlay() override;

protected:

    UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_EffectValue)
    FFloatParameter EffectValue;

    UPROPERTY(EditAnywhere)
    FGameplayTagContainer AffectingTag;

    UPROPERTY(EditAnywhere)
    TEnumAsByte<EAffectingType> AffectingType;

    FTimerHandle PeriodTimer;

    UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_DurationParameter)
    FFloatParameter DurationParameter;

    UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_PeriodParameter, Category = "Period")
    FFloatParameter PeriodParameter;

    UPROPERTY(EditAnywhere, Category = "Period")
    uint8 bStartPeriodicTickWhenApply : 1;

    UPROPERTY(EditAnywhere, Instanced, Replicated, Category = "Period")
    TArray<class USpellTask*> PeriodTasks;

    FTimerHandle DurationTimer;

    UPROPERTY(ReplicatedUsing = OnRep_Caster)
    USpellCastManagerComponent* Caster;

    UPROPERTY(ReplicatedUsing = OnRep_EffectOwner)
    USpellCastManagerComponent* Owner;

    TArray<FFloatParameter*> AllFloatParameters;

    UFUNCTION()
    virtual void OnRep_EffectValue(FFloatParameter const& OldEffectValue);

    UFUNCTION()
    virtual void OnRep_DurationParameter(FFloatParameter const& OldDurationParameter);

    UFUNCTION()
    virtual void OnRep_PeriodParameter(FFloatParameter const& OldPeriodParameter);

    UFUNCTION()
    virtual void OnRep_Caster();

    UFUNCTION()
    virtual void OnRep_EffectOwner();

    virtual void OnPeriodChanged();

    virtual void OnPeriodTick();

    virtual void RecalculateDependentParameters(float NewModifierValue);

    virtual void DurationExpired();

    virtual void RegisterParameters(uint32 CountOfParameters);

    virtual void InitializeParameters();

    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

    

private:

    UPROPERTY()
    USpellCastData* CastData;

    TArray<FFloatParameter*> DependentFloatParameters;
};
