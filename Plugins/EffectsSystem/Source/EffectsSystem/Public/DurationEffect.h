// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PermanentEffect.h"
#include "DurationEffect.generated.h"

/**
 * 
 */
UCLASS()
class EFFECTSSYSTEM_API UDurationEffect : public UPermanentEffect
{
	GENERATED_BODY()


public:

    FORCEINLINE virtual bool HasDuration() const { return true; }

    FORCEINLINE virtual bool IsInstant() const { return false; }

    FORCEINLINE virtual bool IsPermanent() const { return false; }

    virtual void RegisteringAllParameters  (USpellCastManagerComponent* ParamsOwner) override;
    virtual void UnregisteringAllParameters(USpellCastManagerComponent* ParamsOwner) override;

protected:

    virtual void BeginPlay(UWorld* World) override;
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

    UPROPERTY(EditAnywhere, Category = "Duration")
    FFloatParameter Duration;

    FTimerHandle DurationTimer;

private:

    virtual void Expired();
	
};
