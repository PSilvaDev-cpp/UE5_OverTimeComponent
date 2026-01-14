// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GE_CooldownBase.h"

#include "GA_AbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BASICS01_API UGA_AbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_AbilityBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	TSubclassOf<UGE_CooldownBase> CooldownEffectClass;

	


protected:

	bool CommitOrCancel(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo);

	virtual const FGameplayTagContainer* GetCooldownTags() const override;
	virtual UGameplayEffect* GetCooldownGameplayEffect() const override;

	void SetupCooldownTags();

};
