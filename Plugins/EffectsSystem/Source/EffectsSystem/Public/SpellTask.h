// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FloatParameter.h"
#include "SpellTask.generated.h"

class USpellCastData;
class USpellCastManagerComponent;
class UAbilityBase;

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced, editinlinenew)
class EFFECTSSYSTEM_API USpellTask : public UObject
{
    GENERATED_BODY()

protected:

    virtual void InitializeAllFloatParameters();

    virtual void RegisteringAllFloatParameters() {}
    virtual void UnregisteringAllFloatParameters();

    UPROPERTY(EditAnywhere, Instanced, Category = "==========================================================================")
    TArray<USpellTask*> NextTasks;

private:

    UPROPERTY()
    AActor* ActorOwner;

    UPROPERTY()
    USpellCastManagerComponent* Owner;

    UPROPERTY()
    UAbilityBase* AbilityOwner;

    TArray<FFloatParameter*> AllFloatParameters;

public:

    ~USpellTask();

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData);

    virtual void PostInitProperties() override;

    virtual void BeginDestroy() override;

    static void RunTaskList(TArray<USpellTask*> const& TaskList, USpellCastManagerComponent* Target, USpellCastData* CastData);

    void RegisterFloatParameter(FFloatParameter* NewParam);

    FORCEINLINE AActor* GetActorOwner() const
    {
        return ActorOwner;
    }

    FORCEINLINE USpellCastManagerComponent* GetOwner() const
    {
        return Owner;
    }

    FORCEINLINE UAbilityBase* GetAbilityOwner() const
    {
        return AbilityOwner;
    }
};


