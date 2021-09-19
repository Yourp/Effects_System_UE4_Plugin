// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellTask.h"
#include "AbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class EFFECTSSYSTEM_API UAbilityBase : public UObject
{
	GENERATED_BODY()
	
    

public:

    DECLARE_DELEGATE_RetVal(uint64, FAbilityCastCheck);

    virtual void CastSpellTo(USpellCastManagerComponent* Target);

    void AddCheckCastDelegate(FAbilityCastCheck& CheckDelegate);

    uint64 IsCantCast() const;

private:

    virtual USpellCastData* CreateSpellCastData();

    UPROPERTY(EditAnywhere)
    TSubclassOf<USpellCastData> CastData;

    UPROPERTY(EditAnywhere, Instanced)
    TArray<USpellTask*> SpellTasks;

    TArray<FAbilityCastCheck> CastChecks;
};
