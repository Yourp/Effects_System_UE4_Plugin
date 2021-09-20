// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "FloatParameter.generated.h"

class USpellCastManagerComponent;
class USpellEffect;
struct FAffectingInfo;
struct FFloatParameter;

UENUM()
enum EAffectingType
{
    Affect_Modify,
    Affect_Multiply,
    Affect_Max          UMETA(Hidden)
};

class EFFECTSSYSTEM_API AffectingMethod
{
public:
    virtual ~AffectingMethod() {}

    AffectingMethod() {}

    virtual void Affect(FAffectingInfo const& Info) = 0;
    virtual void Affect(FFloatParameter& ChangedParameter, float ModValue) = 0;
};

class EFFECTSSYSTEM_API ModifyAffect : public AffectingMethod
{
public:

    virtual void Affect(FAffectingInfo const& Info) override;
    virtual void Affect(FFloatParameter& ChangedParameter, float ModValue) override;
};

class EFFECTSSYSTEM_API MultiplyAffect : public AffectingMethod
{
public:

    virtual void Affect(FAffectingInfo const& Info) override;
    virtual void Affect(FFloatParameter& ChangedParameter, float ModValue) override;
};

USTRUCT(BlueprintType)
struct EFFECTSSYSTEM_API FFloatParameter
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FAfterChange, FAffectingInfo const&);

private:

    UPROPERTY()
    float Value;

    UPROPERTY(NotReplicated, EditDefaultsOnly)
    float BaseValue;

    UPROPERTY(NotReplicated, EditDefaultsOnly)
    FGameplayTag ParameterName;

    TArray<USpellEffect const*> AddingEffects;
    TArray<USpellEffect const*> TotalMultiplyingEffects;
    TArray<USpellEffect const*> TotalMultiplyingEffectsNotStack;
    
    UPROPERTY()
    float Adding;

    UPROPERTY()
    float Multiplying;

    FAfterChange AfterChangeDelegate;

public:

    FFloatParameter() : Multiplying(1.f) {}

    static AffectingMethod* AffectingMethods[EAffectingType::Affect_Max];

    FORCEINLINE void Initialize() { Value = BaseValue; }

    FORCEINLINE const FGameplayTag& GetGameplayTag() const { return ParameterName; }

    FORCEINLINE float GetValue()       const { return       Value; }
    FORCEINLINE float GetBaseValue()   const { return   BaseValue; }

    FORCEINLINE float GetAdding()      const { return      Adding; }
    FORCEINLINE float GetMultiplying() const { return Multiplying; }

    FORCEINLINE void SetValue    (float NewValue)   { Value       = NewValue; }
    FORCEINLINE void SetBaseValue(float NewValue)   { BaseValue   = NewValue; }

    void SetGameplayTag(const FGameplayTag& NewTag) { ParameterName = NewTag; }

    void MultiplyInstant(float   Rate);
    void ModifyInstant  (float Amount);
    
    void MultiplyLong(FAffectingInfo const& Info);
    void ModifyLong  (FAffectingInfo const& Info);

    FORCEINLINE FAfterChange& GetAfterChangeDelegate() { return AfterChangeDelegate; };

    FORCEINLINE void Recalculate()
    {
        Value = (BaseValue + Adding) * Multiplying;
    }

    FORCEINLINE bool operator >  (float Val) const { return Value >  Val; }
    FORCEINLINE bool operator == (float Val) const { return Value == Val; }
    FORCEINLINE bool operator <  (float Val) const { return Value <  Val; }
    FORCEINLINE void operator =  (float Val)       {        Value =  Val; }
    FORCEINLINE void operator *= (float Val)       {        Value *= Val; }
    FORCEINLINE void operator -= (float Val)       {        Value -= Val; }
    FORCEINLINE void operator /= (float Val)       {        Value /= Val; }
    FORCEINLINE void operator += (float Val)       {        Value += Val; }

    FORCEINLINE operator float () { return Value; }
};






