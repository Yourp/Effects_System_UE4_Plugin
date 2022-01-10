// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellCastManagerComponent.h"
#include "../../Abilities/Effects/LimitedResources.h"
#include "FightManagerComponent.generated.h"

class UAbilityBase;
// class ULimitedResources;
// class USpellEffect;

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UFightManagerComponent : public USpellCastManagerComponent
{
    GENERATED_BODY()


public:

    UFightManagerComponent();

    DECLARE_MULTICAST_DELEGATE_OneParam(FTestDelegateSSS, float)

    FTestDelegateSSS TestDelegate;

    void TestFunc();
    void TestDelegateFunc();

    float GetHealthPct() const;

    virtual void BeginPlay() override;

    virtual void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker);

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

private:

    UPROPERTY(EditAnywhere, Instanced)
    ULimitedResources* Health;

    UPROPERTY(EditAnywhere, Instanced)
    ULimitedResources* Energy;

    UPROPERTY(EditAnywhere, Instanced)
    USpellEffect* SpellPower;

    UPROPERTY(EditAnywhere, Instanced)
    USpellEffect* Haste;

    UPROPERTY(EditAnywhere, Instanced)
    USpellEffect* CritChance;

    UPROPERTY(EditAnywhere, Instanced)
    USpellEffect* CritMultiplying;

    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<UAbilityBase>> AbilitiesDefault;

    UPROPERTY(ReplicatedUsing = OnRep_Abilities)
    TArray<UAbilityBase*> Abilities;

    UFUNCTION(NetMulticast, Reliable)
    void EmptyTest();

protected:

    UFUNCTION()
    virtual void OnRep_Abilities(TArray<UAbilityBase*> OldAbilities);
};
