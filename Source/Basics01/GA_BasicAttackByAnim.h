// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_AbilityBase.h"
#include "GA_BasicAttackByAnim.generated.h"

/**
 * 
 */
UCLASS()
class BASICS01_API UGA_BasicAttackByAnim : public UGA_AbilityBase
{
	GENERATED_BODY()

public:
	UGA_BasicAttackByAnim();


protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnAttackWindowStart(FGameplayEventData Payload);

	UFUNCTION()
	void OnAttackWindowEnd(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

};
