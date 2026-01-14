// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagsManager.h"
#include <GameplayEffectComponents/TargetTagsGameplayEffectComponent.h>
#include "GE_CooldownBase.generated.h"

/**
 * 
 */
UCLASS()
class BASICS01_API UGE_CooldownBase : public UGameplayEffect
{
	GENERATED_BODY()
	
public:

	UGE_CooldownBase();

protected:

	UTargetTagsGameplayEffectComponent* TargetTagsComponent;

};
