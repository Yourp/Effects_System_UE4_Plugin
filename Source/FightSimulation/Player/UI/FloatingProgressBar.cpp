// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingProgressBar.h"
#include "GameFramework/HUD.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/Canvas.h"


void FFloatingProgressBar::Draw(FVector Point, float FillingOfBar, AHUD* HUD, UCanvas* Canvas)
{
    if (!ColorCurve || !BackgroundColorCurve)
    {
        return;
    }

    /** Transforms our 3D world space vector to 2D screen coordinates. */
    FVector Location2D = Canvas->Project(Point);

    if (!Location2D.Z)
    {
        /** We don't need to draw, if bar is behind the screen. */
        return;
    }

    FLinearColor Color              = ColorCurve            ->GetLinearColorValue(FillingOfBar);
    FLinearColor BackgroundColor    = BackgroundColorCurve  ->GetLinearColorValue(FillingOfBar);

    float        XLocation          = Location2D.X - Width  / 2.f;
    float        YLocation          = Location2D.Y - Height / 2.f;

    /** Background. */
    HUD->DrawRect
    (
        BackgroundColor,
        XLocation   - BackgroundSizeDiff,
        YLocation   - BackgroundSizeDiff,
        Width       + BackgroundSizeDiff * 2,
        Height      + BackgroundSizeDiff * 2
    );

    /** Filling line. */
    HUD->DrawRect(Color, XLocation, YLocation, Width * FillingOfBar, Height);
}
