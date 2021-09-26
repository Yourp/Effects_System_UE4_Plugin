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
    Affect_Add         UMETA(DisplayName =      "Add"),
    Affect_Multiply    UMETA(DisplayName = "Multiply"),
    Affect_Max         UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct EFFECTSSYSTEM_API FFloatParameter
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FAfterChange, float);

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

    void UpdateMultiplyingValue();
    void UpdateAddingValue();

    FORCEINLINE void Recalculate()
    {
        Value = Calculate(BaseValue, Adding, Multiplying);
    }

public:

    FFloatParameter() : Multiplying(1.f) {}

    FORCEINLINE void Initialize() { Value = BaseValue; }

    FORCEINLINE const FGameplayTag& GetGameplayTag() const { return ParameterName; }

    FORCEINLINE float GetValue()       const { return       Value; }
    FORCEINLINE float GetBaseValue()   const { return   BaseValue; }

    FORCEINLINE float GetAdding()      const { return      Adding; }
    FORCEINLINE float GetMultiplying() const { return Multiplying; }

    FORCEINLINE void SetBaseValue(float NewValue)
    {
        BaseValue = NewValue;
    }

    void SetValue(float NewValue);


    void SetGameplayTag(const FGameplayTag& NewTag) { ParameterName = NewTag; }

    FORCEINLINE FAfterChange& GetAfterChangeDelegate() { return AfterChangeDelegate; };

    static float Calculate(float Base, float Add, float Multiply);

    FORCEINLINE bool operator >  (float Val) const { return Value >  Val; }
    FORCEINLINE bool operator == (float Val) const { return Value == Val; }
    FORCEINLINE bool operator <  (float Val) const { return Value <  Val; }
    FORCEINLINE void operator =  (float Val)       {        Value =  Val; }
    FORCEINLINE void operator -= (float Val)       {        Value -= Val; }
    FORCEINLINE void operator /= (float Val)       {        Value /= Val; }

    FORCEINLINE operator float () const { return Value; }

    void operator += (float Val);
    void operator *= (float Val);

    void operator += (USpellEffect const* Effect);
    void operator -= (USpellEffect const* Effect);
};






