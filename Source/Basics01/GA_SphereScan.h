// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_AbilityBase.h"
#include "GE_SphereScan_CD.h"
#include "AbilitySystemComponent.h"
#include "GA_SphereScan.generated.h"

/**
 * 
 */
UCLASS()
class BASICS01_API UGA_SphereScan : public UGA_AbilityBase
{
	GENERATED_BODY()
	
public:
	UGA_SphereScan();

protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

public:



};
