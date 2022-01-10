// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ReplicatedObject.h"
#include "SpellTask.h"
#include "SpellEffect.h"
#include "AbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class EFFECTSSYSTEM_API UAbilityBase : public UReplicatedObject
{
	GENERATED_BODY()
	
    

public:

    DECLARE_DELEGATE_RetVal(uint64, FAbilityCastCheck);

    virtual void CastTo(USpellCastManagerComponent* Target);

    void AddCheckCastDelegate   (FAbilityCastCheck* CheckDelegate);
    void RemoveCheckCastDelegate(FAbilityCastCheck* CheckDelegate);

    uint64 IsCantCast() const;

    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

    virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;


private:

    virtual USpellCastData* CreateSpellCastData();

    UPROPERTY(EditAnywhere)
    TSubclassOf<USpellCastData> CastData;

    UPROPERTY(EditAnywhere, Instanced)
    TArray<USpellTask*> SpellTasks;

    TArray<FAbilityCastCheck*> CastChecks;
};
