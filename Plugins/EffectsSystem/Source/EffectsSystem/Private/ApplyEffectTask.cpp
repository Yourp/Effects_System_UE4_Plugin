// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplyEffectTask.h"

void UApplyEffectTask::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    if (Effect != nullptr)
    {
        Target->ApplyEffect(Target, Effect);

        USpellTask::RunTaskList(NextTasks, Target, CastData);
    }
}
