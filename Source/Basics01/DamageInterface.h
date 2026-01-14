// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "DamageInterface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class BASICS01_API UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

class BASICS01_API IDamageInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void OnTakeDamage(float Damage, bool OverTime,
		FName Name,
		bool bAcumulates,
		float Interval,
		float Duration,
		bool Replace);

	virtual void OnTakeDamage_Implementation(float Damage, bool OT,
		FName Name,
		bool bAcumulates,
		float Interval,
		float Duration,
		bool Replace)
	{
		// Default implementation (can be empty)
	}

};
