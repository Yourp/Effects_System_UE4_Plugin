// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectsSystemHelpMacros.h"
#include "SpellCastManagerComponent.generated.h"

class USpellEffect;
class UPermanentEffect;
class USpellCastManagerComponent;
class USpellBase;
struct FFloatParameter;
struct FGameplayTag;
struct FGameplayTagContainer;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EFFECTSSYSTEM_API USpellCastManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellCastManagerComponent();

    UFUNCTION(NetMulticast, Reliable)
    void ApplyEffect(USpellCastManagerComponent* Caster, USpellEffect* Effect);

    UFUNCTION(NetMulticast, Reliable)
    void RemoveEffect(USpellEffect* Effect);

    FFloatParameter* FindFirstParameterByTag(FGameplayTag const& Tag);

    void Impacting(float Amount, FGameplayTagContainer const& ImpactTag, enum EAffectingType Type);

    void ApplyAllModsTo(float& Amount, FGameplayTag const& AmountName);
    void ApplyAllModsTo(FFloatParameter* Param);
    float GetModifierFor   (FGameplayTag const& Tag) const;
    float GetMultiplayerFor(FGameplayTag const& Tag) const;

    void GetAllParametersByTag         (TArray<FFloatParameter*>& ParamList, FGameplayTag          const& Tag);
    void GetAllParametersByTagContainer(TArray<FFloatParameter*>& ParamList, FGameplayTagContainer const& Tag);

    void RegisteringAppliedEffect  (USpellEffect* Effect);
    void UnregisteringAppliedEffect(USpellEffect* Effect);

    void RegisterFloatParameter  (FFloatParameter* NewParamPtr);
    void UnregisterFloatParameter(FFloatParameter* NewParamPtr);

    TArray<FFloatParameter*> const& GetAllParametersWithTags() const;

    TArray<USpellEffect*> const& GetAppliedEffects() const;

    virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

    
    UFUNCTION()
    virtual void OnRep_AppliedEffects(TArray<USpellEffect*> Old);

	/** Called when the game starts. */
	virtual void BeginPlay() override;

private:

    TArray<FFloatParameter*> AllFloatParameters;

    TArray<FFloatParameter*> AllParametersWithTags;

    UPROPERTY(ReplicatedUsing = OnRep_AppliedEffects)
    TArray<USpellEffect*> AppliedEffects;

    virtual void InitializeFloatParameters() {}



private:


public:

};


