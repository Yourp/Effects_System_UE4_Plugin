// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FloatingProgressBar.generated.h"

class UCurveLinearColor;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIGHTSIMULATION_API FFloatingProgressBar
{
    GENERATED_BODY()

private:

    UPROPERTY(EditAnywhere)
    float Width;

    UPROPERTY(EditAnywhere)
    float Height;

    UPROPERTY(EditAnywhere)
    float BackgroundSizeDiff;

    UPROPERTY(EditAnywhere)
    UCurveLinearColor* ColorCurve;

    UPROPERTY(EditAnywhere)
    UCurveLinearColor* BackgroundColorCurve;

public:

    void Draw(FVector Point, float FillingOfBar, class AHUD* HUD, UCanvas* Canvas);
};
