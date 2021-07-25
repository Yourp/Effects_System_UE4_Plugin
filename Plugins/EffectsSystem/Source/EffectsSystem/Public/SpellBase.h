// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "FloatParameter.h"
#include "SpellBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class EFFECTSSYSTEM_API USpellBase : public UReplicatedObject
{
	GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCooldownExpired, USpellBase const*);
	
private:

    UPROPERTY(EditAnywhere)
    FFloatParameter RecoveryTime;

    FTimerHandle Cooldown;

    FOnCooldownExpired OnCooldownExpiredDelegate;

    virtual void CooldownExpired();

public:

    bool IsHasCooldown() const;

    virtual void  SetCooldown(float NewCooldown);
    virtual float GetCooldownTime() const;

    FORCEINLINE USpellBase::FOnCooldownExpired& GetOnCooldownExpiredDelegate()
    {
        return OnCooldownExpiredDelegate;
    }
};
