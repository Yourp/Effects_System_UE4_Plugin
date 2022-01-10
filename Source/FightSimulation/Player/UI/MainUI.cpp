// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

void UMainUI::PlayFloatDamage()
{
    if (DamageNonCritAnim)
    {
        UWidgetAnimation* CreatedAnim = NewObject<UWidgetAnimation>(this, NAME_None, RF_NoFlags, DamageNonCritAnim);
        PlayAnimation(CreatedAnim, 1);
        PlayAnimation(DamageNonCritAnim);

        FTimerHandle dd;
        GetWorld()->GetTimerManager().SetTimer(dd, this, &UMainUI::PlayFloatDamage, 1);
    }
}
