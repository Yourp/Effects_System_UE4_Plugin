// Fill out your copyright notice in the Description page of Project Settings.


#include "FFloatParameterTest.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "../Public/FloatParameter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFloatParameterInitializationTest, "EffectSystem.FloatParameter",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter |
                                 EAutomationTestFlags::HighPriority);


bool FFloatParameterInitializationTest::RunTest(const FString& Parameters)
{
    FFloatParameter TestParameter;

    AddInfo("FFloatParameter: Initialization...");
    {
        TestParameter.SetBaseValue(1000.f);
        TestParameter.Initialize();
        TestTrueExpr(TestParameter.GetValue() == 1000.f);
    }

    AddInfo("FFloatParameter: GetBaseValue after SetValue...");
    {
        TestParameter.SetValue(500.f);
        TestTrueExpr(TestParameter.GetBaseValue() == 1000.f);
    }

    AddInfo("FFloatParameter: GetValue and GetBaseValue after repeated initialization...");
    {
        TestParameter.Initialize();
        TestTrueExpr(TestParameter.GetValue()     ==  500.f);
        TestTrueExpr(TestParameter.GetBaseValue() == 1000.f);
    }
    
    AddInfo("FFloatParameter: += operator...");
    {
        TestParameter += 100.f;
        TestTrueExpr(TestParameter.GetValue()     ==  600.f);
        TestTrueExpr(TestParameter.GetBaseValue() == 1100.f);

        TestParameter += -100.f;
        TestTrueExpr(TestParameter.GetValue()     ==  500.f);
        TestTrueExpr(TestParameter.GetBaseValue() == 1000.f);
    }

    AddInfo("FFloatParameter: *= operator...");
    {
        TestParameter *= 0.5f;
        TestTrueExpr(TestParameter.GetValue()     == 250.f);
        TestTrueExpr(TestParameter.GetBaseValue() == 500.f);
    }

    return true;
}




