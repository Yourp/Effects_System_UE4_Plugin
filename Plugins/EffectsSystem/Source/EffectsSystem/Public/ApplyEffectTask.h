// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTask.h"
#include "ApplyEffectTask.generated.h"

class USpellEffect;

/** The data for tag renaming. */
USTRUCT()
struct FTagRenamerData
{
    GENERATED_BODY()

    /** The tag name which need to be renamed. */
    UPROPERTY(EditAnywhere)
    FGameplayTagContainer   Names;

    /** The tag name after renaming. */
    UPROPERTY(EditAnywhere)
    FGameplayTag            NewName;
};

/**
 * 
 */
UCLASS(meta = (DisplayName = "Apply Effect"))
class EFFECTSSYSTEM_API UApplyEffectTask : public USpellTask
{
	GENERATED_BODY()
	
public:

    virtual void Run(USpellCastManagerComponent* Target, USpellCastData* CastData) override;

    virtual void RenameParameters(TArray<FFloatParameter*> const& Params);

    virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

    virtual void BeginPlay() override;

    FORCEINLINE bool HasNewTagNames() const
    {
        return ListOfNewTagsName.Num() > 0;
    }

    FORCEINLINE USpellEffect* GetEffect() const
    {
        return Effect;
    }

private:

    UPROPERTY(EditAnywhere)
    TArray<FTagRenamerData> ListOfNewTagsName;

    UPROPERTY(EditAnywhere, Instanced)
    USpellEffect* Effect;

protected:

    virtual USpellEffect* CreateEffect();

    virtual void FillInParameters() override;
};
