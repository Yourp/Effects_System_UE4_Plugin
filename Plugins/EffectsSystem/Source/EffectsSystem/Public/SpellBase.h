// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "FloatParameter.h"
#include "SpellTargetMethodBase.h"
#include "SpellBase.generated.h"

class USpellCastManagerComponent;



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

    UPROPERTY(EditAnywhere)
    FFloatParameter CastTime;

    UPROPERTY(EditAnywhere)
    FFloatParameter FlySpeed;

    UPROPERTY(EditAnywhere, Instanced)
    TArray<USpellTargetMethodBase*> TargetMethod;

    USpellCastManagerComponent* Owner;

    FTimerHandle Cooldown;

    FTimerHandle CastDelay;

    FOnCooldownExpired OnCooldownExpiredDelegate;

    bool IsTimerPending(FTimerHandle const& Timer) const;

    virtual void CooldownExpired();

public:

    bool IsHasCooldown() const;
    bool IsInCastDelay() const;

    virtual void  SetCooldown(float NewCooldown);
    virtual float GetCooldownTime() const;

    virtual bool IsCanCast() const;

    void SetOwner(USpellCastManagerComponent* NewOwner);

    FORCEINLINE USpellCastManagerComponent const* GetOwner() const
    {
        return Owner;
    }

    FORCEINLINE USpellBase::FOnCooldownExpired& GetOnCooldownExpiredDelegate()
    {
        return OnCooldownExpiredDelegate;
    }
};
