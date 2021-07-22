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

    virtual void BeginPlay(UWorld* World) {}
    virtual void Destroy();

    UFUNCTION()
    ENetRole GetOwnerRole() const;

    FORCEINLINE AActor* GetActorOuter() const { return MyActorOuter; }

    virtual bool IsSupportedForNetworking() const override;
    virtual bool CallRemoteFunction(UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack) override;
    virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
    virtual void PostInitProperties() override;

private:

    UPROPERTY()
    AActor* MyActorOuter;
};


