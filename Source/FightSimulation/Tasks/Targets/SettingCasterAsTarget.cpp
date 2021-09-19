// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingCasterAsTarget.h"
#include "SpellCastData.h"

void USettingCasterAsTarget::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    RunTaskList(NextTasks, CastData->GetCaster(), CastData);
}
