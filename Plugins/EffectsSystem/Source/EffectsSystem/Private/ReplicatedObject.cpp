// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplicatedObject.h"

bool UReplicatedObject::IsSupportedForNetworking() const
{
    return true;
}

bool UReplicatedObject::CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack)
{
    if (AActor* MyOwner = GetActorOuter())
    {
        if (UNetDriver* NetDriver = MyOwner->GetNetDriver())
        {
            NetDriver->ProcessRemoteFunction(MyOwner, Function, Parms, OutParms, Stack, this);
            return true;
        }
    }

    return false;
}

int32 UReplicatedObject::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
    return GetOuter() ? GetOuter()->GetFunctionCallspace(Function, Stack) : FunctionCallspace::Local;
}

void UReplicatedObject::PostInitProperties()
{
    Super::PostInitProperties();

    UObject* CurrentOuter = GetOuter();

    while (CurrentOuter)
    {
        MyActorOuter = Cast<AActor>(CurrentOuter);

        if (MyActorOuter != nullptr)
        {
            break;
        }

        CurrentOuter = CurrentOuter->GetOuter();
    }

    if (MyActorOuter != nullptr)
    {
        if (UWorld* World = MyActorOuter->GetWorld())
        {
            BeginPlay(World);
        }
    }
}

ENetRole UReplicatedObject::GetOwnerRole() const
{
    AActor* MyOwner = GetActorOuter();
    return (MyOwner ? MyOwner->GetLocalRole() : ROLE_None);
}

void UReplicatedObject::Destroy()
{
    MyActorOuter = nullptr;
    MarkPendingKill();
}


