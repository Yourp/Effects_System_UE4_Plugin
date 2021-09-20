// Fill out your copyright notice in the Description page of Project Settings.


#include "DelayedTask.h"
#include "AbilityBase.h"
#include "EffectsSystemHelpMacros.h"


void UDelayedTask::Run(USpellCastManagerComponent* Target, USpellCastData* CastData)
{
    FTimerDelegate        TimerDelegate;
    FTimerHandle          TimerHandle;
    FDelayedTaskTimerData TimerData;

    TimerData.Target    = Target;
    TimerData.CastData  = CastData;

    TimersData.Add(TimerData);

    TimerDelegate.BindUFunction(this, FName("Execute"), TimerData);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Delay, false);
}

void UDelayedTask::Execute(FDelayedTaskTimerData& Data)
{
    USpellTask::RunTaskList(NextTasks, Data.Target, Data.CastData);
    TimersData.RemoveSwap(Data);
}


