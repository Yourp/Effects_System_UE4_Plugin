// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "FloatParameter.h"
#include "Cooldown.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UCooldown : public USpellTask
{
	GENERATED_BODY()
	

protected:

    virtual void CooldownExpired();

    virtual void FillInParameters() override;

public:

    UCooldown();

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCooldownExpired, UCooldown const*);

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;

    uint64 IsHasCooldown() const;

    virtual void  SetCooldown(float NewCooldown);
    virtual float GetCooldownTime() const;

    virtual void PostInitProperties() override;


private:

    

    UPROPERTY(EditAnywhere)
    FFloatParameter RecoveryTime;

    FTimerHandle CooldownTimer;

    FOnCooldownExpired OnCooldownExpiredDelegate;
};
