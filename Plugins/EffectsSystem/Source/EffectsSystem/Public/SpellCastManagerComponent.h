// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectsSystemHelpMacros.h"
#include "SpellCastManagerComponent.generated.h"

class USpellEffect;
class UPermanentEffect;
class USpellCastManagerComponent;
struct FFloatParameter;
struct FGameplayTag;
struct FGameplayTagContainer;


struct FAffectingInfo
{
    FAffectingInfo
    (
        USpellCastManagerComponent const* NewOwner,
        USpellCastManagerComponent const* NewInitiator,
        FFloatParameter& NewChangedParameter,
        float NewModifierValue,
        USpellEffect const* NewEffect,
        bool bIsApply
    );

    USpellCastManagerComponent const* Owner;
    USpellCastManagerComponent const* Initiator;
    FFloatParameter& ChangedParameter;
    float ModifierValue;
    USpellEffect const* Effect;
    float OldParameterValue;
    bool bIsApplying;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EFFECTSSYSTEM_API USpellCastManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellCastManagerComponent();

    UFUNCTION(NetMulticast, Reliable)
    void ApplyEffect(USpellCastManagerComponent* Caster, UClass* EffectClass);

    UFUNCTION(NetMulticast, Reliable)
    void RemoveEffect(UPermanentEffect* Effect);

    FFloatParameter* FindFirstParameterByTag(FGameplayTag const& Tag);

    void GetAllParametersByTag         (TArray<FFloatParameter*>& ParamList, FGameplayTag          const& Tag);
    void GetAllParametersByTagContainer(TArray<FFloatParameter*>& ParamList, FGameplayTagContainer const& Tag);

    void TakeAllTagParametersFrom(UPermanentEffect* Effect);
    void RemoveAllTagParametersOf(UPermanentEffect* Effect);

    void RegisteringAppliedEffect  (UPermanentEffect* Effect);
    void UnregisteringAppliedEffect(UPermanentEffect* Effect);

    TArray<FFloatParameter*> const& GetAllParametersWithTags() const;

    virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

protected:

    

    void RegisterFloatParameter(FFloatParameter* NewParamPtr);

	// Called when the game starts
	virtual void BeginPlay() override;

private:

    TArray<FFloatParameter*> AllFloatParameters;

    TArray<FFloatParameter*> AllParametersWithTags;

    TArray<UPermanentEffect*> AppliedEffects;

    virtual void InitializeFloatParameters() {}

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:


public:

};


