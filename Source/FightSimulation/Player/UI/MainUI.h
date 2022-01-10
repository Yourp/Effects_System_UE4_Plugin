// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API UMainUI : public UUserWidget
{
	GENERATED_BODY()
	

private:

    UPROPERTY(meta = (BindWidgetAnim))
    UWidgetAnimation* DamageNonCritAnim;

public:

    void PlayFloatDamage();
};
