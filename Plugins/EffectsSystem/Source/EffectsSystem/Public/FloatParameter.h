// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "FloatParameter.generated.h"

class USpellCastManagerComponent;
class USpellEffect;

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

    DECLARE_DELEGATE_OneParam          (FOnChange,    float&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FAfterChange, float );

private:

    UPROPERTY()
    float Value;

    UPROPERTY(NotReplicated, EditAnywhere)
    float BaseValue;

    UPROPERTY(NotReplicated, EditAnywhere)
    FGameplayTag ParameterName;

    UPROPERTY(NotReplicated)
    uint8 bIsInitialized : 1;

    TArray<USpellEffect*> AddingEffects;
    TArray<USpellEffect*> TotalMultiplyingEffects;
    
    UPROPERTY()
    float Adding;

    UPROPERTY()
    float Multiplying;

    FOnChange    OnChangeDelegate;
    FAfterChange AfterChangeDelegate;

    void ClearListOfMods(TArray<USpellEffect*>& List);

public:

    FFloatParameter() : bIsInitialized(false), Multiplying(1.f) {}

    void Initialize();

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

    void RemoveAllMods();

    void UpdateMultiplyingValue();
    void UpdateAddingValue();

    void Recalculate();

    void SetGameplayTag(const FGameplayTag& NewTag) { ParameterName = NewTag; }

    FORCEINLINE FOnChange&    GetOnChangeDelegate()    { return    OnChangeDelegate; };
    FORCEINLINE FAfterChange& GetAfterChangeDelegate() { return AfterChangeDelegate; };

    static float Calculate(float Base, float Add, float Multiply);

    FORCEINLINE bool operator >  (float Val) const {  return Value >  Val;  }
    FORCEINLINE bool operator == (float Val) const {  return Value == Val;  }
    FORCEINLINE bool operator <  (float Val) const {  return Value <  Val;  }

    FORCEINLINE operator float () const { return Value; }

    void operator  = (float Val);
    void operator += (float Val);
    void operator *= (float Val);

    void operator += (USpellEffect* Effect);
    void operator -= (USpellEffect* Effect);

    void operator = (FFloatParameter const& Template)
    {
        Value           = Template.Value;
        BaseValue       = Template.BaseValue;
        ParameterName   = Template.ParameterName;
        bIsInitialized  = Template.bIsInitialized;
    }
};






