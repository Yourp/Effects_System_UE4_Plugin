// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "FloatParameter.h"
#include "ImpactingTask.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Impact"))
class EFFECTSSYSTEM_API UImpactingTask : public USpellTask
{
	GENERATED_BODY()
	
public:

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;

    virtual float GetCalculatedValue(USpellCastManagerComponent* Target, USpellCastData* CastData);

    virtual void AffectToTarget(USpellCastManagerComponent* Target, float Amount);

    virtual void FillInParameters() override;

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const;

private:

    UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_ModValue)
    FFloatParameter ModValue;

    UPROPERTY(EditAnywhere)
    FGameplayTagContainer AffectingTag;

    UPROPERTY(EditAnywhere)
    FGameplayTag TagForTargetMods;

    UPROPERTY(EditAnywhere)
    TEnumAsByte<EAffectingType> AffectingType;

protected:

    UFUNCTION()
    virtual void OnRep_ModValue(FFloatParameter const& OldValue);
};
