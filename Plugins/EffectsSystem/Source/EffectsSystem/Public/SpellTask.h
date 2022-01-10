// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ReplicatedObject.h"
#include "FloatParameter.h"
#include "SpellTask.generated.h"

class USpellCastData;
class USpellCastManagerComponent;
class UAbilityBase;

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced, editinlinenew)
class EFFECTSSYSTEM_API USpellTask : public UReplicatedObject
{
    GENERATED_BODY()

protected:

    DECLARE_DELEGATE_RetVal(uint64, FAbilityCastCheck);

    virtual void FillInParameters() {}
    virtual void UnregisteringAllFloatParameters();
    virtual void RegisteringAllParametersForOwner();

    UFUNCTION()
    virtual void OnRep_ActorOwner();

    UFUNCTION()
    virtual void OnRep_ComponentOwner();

    UFUNCTION()
    virtual void OnRep_AbilityOwner();

    FAbilityCastCheck CastCheckDelegate;

    UPROPERTY(EditAnywhere, Instanced, Category = "==========================================================================")
    TArray<USpellTask*> NextTasks;

private:

    UPROPERTY(ReplicatedUsing = OnRep_ActorOwner)
    AActor* ActorOwner;

    UPROPERTY(ReplicatedUsing = OnRep_ComponentOwner)
    USpellCastManagerComponent* ComponentOwner;

    UPROPERTY(ReplicatedUsing = OnRep_AbilityOwner)
    UAbilityBase* AbilityOwner;

    TArray<FFloatParameter*> AllFloatParameters;

public:

    ~USpellTask();

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData);

    virtual void BeginPlay() override;

    virtual void BeginDestroy() override;

    virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

    static void RunTaskList(TArray<USpellTask*> const& TaskList, USpellCastManagerComponent* Target, USpellCastData* CastData);

    void AddFloatParameter(FFloatParameter* NewParam);

    FORCEINLINE AActor* GetActorOwner() const
    {
        return ActorOwner;
    }

    FORCEINLINE USpellCastManagerComponent* GetComponentOwner() const
    {
        return ComponentOwner;
    }

    FORCEINLINE UAbilityBase* GetAbilityOwner() const
    {
        return AbilityOwner;
    }

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;
};


