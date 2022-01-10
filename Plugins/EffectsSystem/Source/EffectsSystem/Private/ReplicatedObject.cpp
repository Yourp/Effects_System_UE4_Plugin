// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplicatedObject.h"
#include "StaticHelper.h"
#include "Net/UnrealNetwork.h"

void UReplicatedObject::OnRep_HasBegunPlay()
{
    if (HasBegunPlay())
    {
        BeginPlay();
    }
}

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
    return GetActorOuter() ? GetActorOuter()->GetFunctionCallspace(Function, Stack) : FunctionCallspace::Remote;
}

void UReplicatedObject::PostInitProperties()
{
    Super::PostInitProperties();

    MyActorOuter = FStaticHelper::FindFirstOuterByClass<AActor>(this);
}

void UReplicatedObject::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UReplicatedObject, bHasBegunPlay);
}

bool UReplicatedObject::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    return false;
}

ENetRole UReplicatedObject::GetOwnerRole() const
{
    AActor* MyOwner = GetActorOuter();
    return (MyOwner ? MyOwner->GetLocalRole() : ROLE_None);
}

void UReplicatedObject::BeginPlay()
{
    bHasBegunPlay = true;
}

void UReplicatedObject::Destroy()
{
    MyActorOuter = nullptr;
    MarkPendingKill();
}


