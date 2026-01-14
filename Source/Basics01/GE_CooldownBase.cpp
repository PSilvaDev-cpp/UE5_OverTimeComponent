// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_CooldownBase.h"

UGE_CooldownBase::UGE_CooldownBase()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	TargetTagsComponent = CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>(TEXT("TargetTagsComponent"));
}