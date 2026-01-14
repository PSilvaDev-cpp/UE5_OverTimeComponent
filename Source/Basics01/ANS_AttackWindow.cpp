// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_AttackWindow.h"
#include "AbilitySystemBlueprintLibrary.h"

void UANS_AttackWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;
	
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)return;

	FGameplayEventData EventData;
	EventData.Instigator = Owner;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, FGameplayTag::RequestGameplayTag("Event.Atack.WindowStart"), EventData);
}

void UANS_AttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;

	AActor* Owner = MeshComp->GetOwner();
	
	if (!Owner)return;
	
	FGameplayEventData EventData;
	EventData.Instigator = Owner;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, FGameplayTag::RequestGameplayTag("Event.Atack.WindowEnd"), EventData);
}