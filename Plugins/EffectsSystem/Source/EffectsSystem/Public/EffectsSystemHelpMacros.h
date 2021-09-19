#pragma once

#define INITIALIZE_FLOAT_PARAMETER(VarName) \
RegisterFloatParameter(&VarName);           \
VarName.Initialize();                       \

#define DECLARE_GETTERS_AND_SETTERS_OF_FLOAT_PARAMETER(VarName)                 \
public:                                                                         \
FORCEINLINE float Get##VarName() const                                          \
{                                                                               \
    return VarName.GetValue();                                                  \
}                                                                               \
FORCEINLINE float Get##VarName##Base() const                                    \
{                                                                               \
    return VarName.GetBaseValue();                                              \
}                                                                               \
FORCEINLINE float Get##VarName##Adding() const                                  \
{                                                                               \
    return VarName.GetAdding();                                                 \
}                                                                               \
FORCEINLINE float Get##VarName##Multiplying() const                             \
{                                                                               \
    return VarName.GetMultiplying();                                            \
}                                                                               \
FORCEINLINE const FGameplayTag& Get##VarName##GameplayTag() const               \
{                                                                               \
    return VarName.GetGameplayTag();                                            \
}                                                                               \
FORCEINLINE FFloatParameter::FAfterChange& Get##VarName##ChangeDelegate()       \
{                                                                               \
    return VarName.GetAfterChangeDelegate();                                    \
}                                                                               \
FORCEINLINE void Set##VarName(float New##VarName##Value)                        \
{                                                                               \
    VarName.SetValue(New##VarName##Value);                                      \
}                                                                               \
FORCEINLINE void Set##VarName##Base(float New##VarName##Value)                  \
{                                                                               \
    VarName.SetBaseValue(New##VarName##Value);                                  \
}                                                                               \
FORCEINLINE void Multiply##VarName##Instant(float Rate)                         \
{                                                                               \
    VarName.MultiplyInstant(Rate);                                              \
}                                                                               \
FORCEINLINE void Modify##VarName##Instant(float Amount)                         \
{                                                                               \
    VarName.ModifyInstant(Amount);                                              \
}                                                                               \

#define INITIALIZE_CHECK_CAST_DELEGATE(FUNC)                    \
if (GetAbilityOwner())                                          \
{                                                               \
    UAbilityBase::FAbilityCastCheck CheckDelegate;              \
    CheckDelegate.BindUObject(this, FUNC);                      \
    GetAbilityOwner()->AddCheckCastDelegate(CheckDelegate);     \
}                                                               \


