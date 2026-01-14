// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BasicAttackByAnim.h"

#include "GameFramework/Character.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"


UGA_BasicAttackByAnim::UGA_BasicAttackByAnim()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bIsCancelable = true;
}


void UGA_BasicAttackByAnim::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitOrCancel(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	//Logic - Trace - Spawn Projectile - HitDetection - ApplyEffect
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	
	if(!Character || !AttackMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("GA_BasicAttackByAnim::ActivateAbility - Missing Character or AttackMontage"));
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	Character->PlayAnimMontage(AttackMontage);

	auto* WaitStart = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Event.AttackWindowStart")));
	
	WaitStart->EventReceived.AddDynamic(this, &UGA_BasicAttackByAnim::OnAttackWindowStart);
	WaitStart->ReadyForActivation();

	auto* WaitEnd = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Event.AttackWindowEnd")));

	WaitEnd->EventReceived.AddDynamic(this, &UGA_BasicAttackByAnim::OnAttackWindowEnd);
	WaitEnd->ReadyForActivation();

	UE_LOG(LogTemp, Warning, TEXT("GA_BasicAttackByAnim::ActivateAbility"));
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_BasicAttackByAnim::OnAttackWindowStart(FGameplayEventData Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("GA_BasicAttackByAnim::OnAttackWindowStart"));
	//Enable Hit Detection
}

void UGA_BasicAttackByAnim::OnAttackWindowEnd(FGameplayEventData Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("GA_BasicAttackByAnim::OnAttackWindowEnd"));
	//Disable Hit Detection
}