// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellCastData.h"
#include "TestCastData.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UTestCastData : public USpellCastData
{
	GENERATED_BODY()
	
public:

    TArray<AActor* > Targets;
};
