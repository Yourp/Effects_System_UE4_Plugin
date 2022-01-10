// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingHUD.h"
#include "MainUI.h"
#include "../../Units/Components/FightManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Caster.h"

AFightingHUD::AFightingHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AFightingHUD::CreateFloatingCombatText(FText const& NewText, FVector const& DrawPoint, EFloatingCombatTextTypes AnimationType)
{
    FloatingTextManager.CreateFloatingCombatText(NewText, DrawPoint, AnimationType);
}

void AFightingHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MainWidgetSubclass)
    {
        /** Create main UMG. */
        MainWidget = CreateWidget<UMainUI>(GetWorld(), MainWidgetSubclass);

        if (MainWidget)
        {
            MainWidget->AddToViewport();
        }
    }
}

void AFightingHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FloatingTextManager.Update(DeltaSeconds);
}

void AFightingHUD::DrawHUD()
{
    Super::DrawHUD();

    FloatingTextManager.DrawAll(Canvas);

    /** Temporary solution. */

    TArray<AActor*> Casters;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UCaster::StaticClass(), Casters);

    for (AActor const* Actor : Casters)
    {
        if (Actor->HasActorBegunPlay() == false)
        {
            continue;
        }

        if (ICaster const* Caster = Cast<ICaster>(Actor))
        {
            if (UFightManagerComponent* FightManagerComponent = Cast<UFightManagerComponent>(Caster->GetSpellCastManagerComponent()))
            {
                FVector Point = Actor->GetActorLocation();
                Point.Z += 130.f;

                FloatingHealthBar.Draw(Point, FightManagerComponent->GetHealthPct(), this, Canvas);
            }
        }
    }
}


