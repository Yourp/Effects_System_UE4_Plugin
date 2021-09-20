// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "DelayedTask.generated.h"

USTRUCT()
struct FIGHTSIMULATION_API FDelayedTaskTimerData
{
    GENERATED_BODY()

public:

    UPROPERTY()
    USpellCastManagerComponent* Target;

    UPROPERTY()
    USpellCastData* CastData;

    FORCEINLINE bool operator == (FDelayedTaskTimerData const& B)
    {
        return CastData == B.CastData;
    }
};

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UDelayedTask : public USpellTask
{
	GENERATED_BODY()
	
private:

    UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
    float Delay;

    UPROPERTY()
    TArray<FDelayedTaskTimerData> TimersData;

public:

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;

    UFUNCTION()
    void Execute(FDelayedTaskTimerData& Data);


};
