// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_SphereScan_CD.h"

UGE_SphereScan_CD::UGE_SphereScan_CD()
{

	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.f));
	

    if (TargetTagsComponent)
    {
        FInheritedTagContainer TagChanges;
        TagChanges.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Cooldown.SphereScan")));
        TargetTagsComponent->SetAndApplyTargetTagChanges(TagChanges);
    }
}
