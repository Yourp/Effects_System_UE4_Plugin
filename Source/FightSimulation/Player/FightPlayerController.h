// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FightPlayerController.generated.h"

class USpellCastManagerComponent;
class UImpactingTask;

USTRUCT()
struct FCombatLogData
{
    GENERATED_BODY()

    UPROPERTY()
    USpellCastManagerComponent* Target;
    
    UPROPERTY(NotReplicated)
    UImpactingTask* Task;

    UPROPERTY()
    int32 Value;

    UPROPERTY()
    uint8 bIsCrit : 1;
};

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API AFightPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

    AFightPlayerController();

    void AddCombatLogData(USpellCastManagerComponent* Caster, USpellCastManagerComponent* Target, UImpactingTask* Task, int32 Value, bool bIsCrit);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void BeginPlay() override;

private:

    UPROPERTY()
    TArray<FCombatLogData> CombatLog;

    FTimerHandle CombatLogTimer;

protected:

    UFUNCTION(Client, Unreliable)
    virtual void SendCombatLogToClients(TArray<FCombatLogData> const& Logs);

    virtual void UpdateCombatLog();
};
