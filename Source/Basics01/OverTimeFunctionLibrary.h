// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimerManager.h"
#include "OverTimeFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BASICS01_API UOverTimeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
/*
	FTimerHandle StartOverTimeFunction(
		FName Name,
		bool bAcumulates,
		float Interval,
		float Duration,
		TFunction<void()> TickFunction,
		TFunction<void()> OnEndFunction,
		bool Replace,
		bool CallOnEndOnReplace
	);
*/
};

