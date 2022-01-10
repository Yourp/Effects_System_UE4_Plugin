// Fill out your copyright notice in the Description page of Project Settings.


#include "FightPlayerController.h"
#include "SpellCastManagerComponent.h"
#include "Net/UnrealNetwork.h"
#include "UI/FightingHUD.h"

AFightPlayerController::AFightPlayerController()
{
    SetReplicates(false);
}

void AFightPlayerController::AddCombatLogData(USpellCastManagerComponent* Caster, USpellCastManagerComponent* Target, UImpactingTask* Task, int32 Value, bool bIsCrit)
{
    FCombatLogData NewData;

    NewData.Target      = Target;
    NewData.Task        = Task;
    NewData.Value       = Value;
    NewData.bIsCrit     = bIsCrit;

    CombatLog.Add(NewData);

    if (UWorld* World = GetWorld())
    {
        if (!World->GetTimerManager().TimerExists(CombatLogTimer))
        {
            World->GetTimerManager().SetTimer(CombatLogTimer, this, &AFightPlayerController::UpdateCombatLog, 0.05f);
        }
    }
}

void AFightPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AFightPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AFightPlayerController::UpdateCombatLog()
{
    if (CombatLog.Num())
    {
        struct Tttt
        {
            USpellCastManagerComponent* Target;
            TArray<TArray<uint8>> Position;
        };

        TArray<Tttt> CompressedTargets;
        int MaxSegments = 0;
        int CompresedSize = CombatLog.Num();

        while (CompresedSize > 8)
        {
            CompresedSize /= 8;
            MaxSegments++;
        }

        if (MaxSegments)
        for (int i = 0; i < CombatLog.Num(); ++i)
        {
            for (auto& Itr : CompressedTargets)
            {
                if (Itr.Target == CombatLog[i].Target)
                {

                }
            }

            // Else
        }

        SendCombatLogToClients(CombatLog);
        CombatLog.Empty(CombatLog.Max());
    }
}

void AFightPlayerController::SendCombatLogToClients_Implementation(TArray<FCombatLogData> const& Logs)
{
    if (AFightingHUD* FHUD = Cast<AFightingHUD>(GetHUD()))
    {
        for (FCombatLogData const& CurrentData : Logs)
        {
            if (CurrentData.Target)
            {
                if (AActor* TargetsOwner = CurrentData.Target->GetOwner())
                {
                    EFloatingCombatTextTypes DamageType   = CurrentData.bIsCrit ? EFloatingCombatTextTypes::CriticalDamageDone : EFloatingCombatTextTypes::NormalDamageDone;
                    FText                    DamageAsText = FText::AsNumber(CurrentData.Value);
                    FVector                  DrawStart    = TargetsOwner->GetActorLocation();

                    DrawStart.Z += 150.f;
                    FHUD->CreateFloatingCombatText(DamageAsText, DrawStart, DamageType);
                }
            }
        }
    }
}




