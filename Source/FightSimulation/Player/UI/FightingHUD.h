// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FloatingCombatText.h"
#include "FloatingProgressBar.h"
#include "FightingHUD.generated.h"

class UMainUI;

/**
 * 
 */
UCLASS()
class FIGHTSIMULATION_API AFightingHUD : public AHUD
{
	GENERATED_BODY()
	
private:

    UPROPERTY(EditAnywhere)
    TSubclassOf<UMainUI> MainWidgetSubclass;

    UPROPERTY()
    UMainUI* MainWidget;

    UPROPERTY(EditAnywhere)
    FFloatingCombatTextManager  FloatingTextManager;

    UPROPERTY(EditAnywhere)
    FFloatingProgressBar        FloatingHealthBar;

public:

    AFightingHUD();

    void CreateFloatingCombatText(FText const& NewText, FVector const& DrawPoint, EFloatingCombatTextTypes AnimationType);

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

    virtual void DrawHUD() override;
};
