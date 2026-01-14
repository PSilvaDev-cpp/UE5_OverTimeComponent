// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_SphereScan.h"
#include "GameFramework/Character.h"

#include "DrawDebugHelpers.h"

UGA_SphereScan::UGA_SphereScan()
{
	CooldownEffectClass = UGE_SphereScan_CD::StaticClass();
	// Set default values or properties here if needed

	SetupCooldownTags();

}

void UGA_SphereScan::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitOrCancel(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}



	

	if(!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AActor* AvatarActor = ActorInfo->AvatarActor.Get();

	FVector Start = AvatarActor->GetActorLocation();
	FVector End = Start;
	float SphereRadius = 2000.f;

	TArray<FHitResult> OutHits;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(SphereRadius);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(AvatarActor);

	if (!GetWorld()) { return; }

	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		Start,
		End,
		FQuat::Identity,
		ECC_WorldDynamic,
		Sphere,
		QueryParams
	);

	DrawDebugSphere(
		GetWorld(),
		Start,
		SphereRadius,
		32,
		FColor::Green,
		false,
		2.0f
	);

	if (bHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			if (ACharacter* HitCaracter = Cast<ACharacter>(Hit.GetActor()))
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.f,
					FColor::Yellow,
					FString::Printf(TEXT("Hit Character: %s"), *HitCaracter->GetName())
				);
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

