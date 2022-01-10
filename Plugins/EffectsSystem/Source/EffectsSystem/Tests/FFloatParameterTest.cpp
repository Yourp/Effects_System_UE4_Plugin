// Fill out your copyright notice in the Description page of Project Settings.


#include "FFloatParameterTest.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "../Public/FloatParameter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFloatParameterInitializationTest, "EffectSystem.FloatParameter.Initialization",
                                 EAutomationTestFlags::ApplicationContextMask |
                                 EAutomationTestFlags::ProductFilter |
                                 EAutomationTestFlags::HighPriority);


bool FFloatParameterInitializationTest::RunTest(const FString& Parameters)
{
    FFloatParameter TestParameter;
    float TestValue = 1000.f;

    AddInfo("Checking initialization...");

    TestParameter.SetBaseValue(TestValue);
    TestParameter.Initialize();
    TestTrueExpr(TestParameter.GetValue() == TestValue);

    AddInfo("Checking mod of base value...");

    TestParameter.SetValue(TestValue / 2.f);
    TestTrueExpr(TestParameter.GetBaseValue() == TestValue);

    AddInfo("Repeated initialization and values check...");

    TestParameter.Initialize();
    TestTrueExpr(TestParameter.GetValue() == (TestValue / 2.f));
    TestTrueExpr(TestParameter.GetBaseValue() == TestValue);

    return true;
}
