// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReplicatedObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class EFFECTSSYSTEM_API UReplicatedObject : public UObject
{
	GENERATED_BODY()
	
public:

    virtual void BeginPlay();
    virtual void Destroy();

    UFUNCTION()
    ENetRole GetOwnerRole() const;

    FORCEINLINE AActor* GetActorOuter() const { return MyActorOuter; }

    /** Indicates that BeginPlay has been called. */
    FORCEINLINE bool HasBegunPlay() const { return bHasBegunPlay; }

    UFUNCTION()
    virtual void OnRep_HasBegunPlay();

    virtual bool IsSupportedForNetworking() const override;
    virtual bool CallRemoteFunction(UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack) override;
    virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
    virtual void PostInitProperties() override;

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const;

    /** Allows a object to replicate other subobject on the actor. */
    virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags);

private:

    UPROPERTY()
    AActor* MyActorOuter;

    /** Indicates that BeginPlay has been called. */
    UPROPERTY(ReplicatedUsing = OnRep_HasBegunPlay)
    uint8 bHasBegunPlay : 1;
};


