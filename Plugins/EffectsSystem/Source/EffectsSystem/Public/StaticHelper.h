// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"

struct EFFECTSSYSTEM_API FStaticHelper
{
private:

    FStaticHelper() {}

public:

    template<class OuterClass>
    static OuterClass* FindFirstOuterByClass(UObject* From);
};

template<class OuterClass>
OuterClass* FStaticHelper::FindFirstOuterByClass(UObject* From)
{
    UObject* CurrentOuter = From->GetOuter();

    while (CurrentOuter)
    {
        OuterClass* MyActorOuter = Cast<OuterClass>(CurrentOuter);

        if (MyActorOuter != nullptr)
        {
            return MyActorOuter;
        }

        CurrentOuter = CurrentOuter->GetOuter();
    }

    return nullptr;
}



