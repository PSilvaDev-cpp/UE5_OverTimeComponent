// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_AbilityBase.h"

void UGA_AbilityBase::SetupCooldownTags()
{
	if (const FGameplayTagContainer* CooldownTags = GetCooldownTags())
	{
		ActivationBlockedTags.AppendTags(*CooldownTags);
	}
}

UGA_AbilityBase::UGA_AbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bIsCancelable = true;

	
}

#include "AbilitySystemComponent.h"

bool UGA_AbilityBase::CommitOrCancel(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();

	if (ASC)
	{
		TArray<FActiveGameplayEffectHandle> ActiveEffects = ASC->GetActiveEffects(FGameplayEffectQuery());

		UE_LOG(LogTemp, Warning, TEXT("Active Effects: %d"), ActiveEffects.Num());
	}

	if (ASC)
	{
		bool bHasCooldown = ASC->HasMatchingGameplayTag(
			FGameplayTag::RequestGameplayTag("State.Cooldown.SphereScan")
		);

		UE_LOG(LogTemp, Warning, TEXT("Has Cooldown Tag: %s"), bHasCooldown ? TEXT("YES") : TEXT("NO"));
	}

	return true;
}



const FGameplayTagContainer* UGA_AbilityBase::GetCooldownTags() const
{
	if (!CooldownEffectClass)
	{
		return nullptr;
	}

	const UGameplayEffect* CooldownGE = CooldownEffectClass->GetDefaultObject<UGameplayEffect>();

	if (!CooldownGE)
	{
		return nullptr;
	}

	return &CooldownGE->GetGrantedTags();
}

UGameplayEffect* UGA_AbilityBase::GetCooldownGameplayEffect() const
{
	if (!CooldownEffectClass) { UE_LOG(LogTemp, Error, TEXT("Cooldown Gameplay Effect INVALID")); return nullptr; }
	UGameplayEffect* GE = CooldownEffectClass->GetDefaultObject<UGameplayEffect>();

	UE_LOG(LogTemp, Warning, TEXT("Cooldown Gameplay Effect Retrieved"));
	
	return GE;
}