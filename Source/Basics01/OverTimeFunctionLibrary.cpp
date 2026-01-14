// Fill out your copyright notice in the Description page of Project Settings.


#include "OverTimeFunctionLibrary.h"
/*
FTimerHandle UOverTimeFunctionLibrary::StartOverTimeFunction(
	FName Name,
	bool bAcumulates,
	float Interval,
	float Duration,
	TFunction<void()> TickFunction,
	TFunction<void()> OnEndFunction,
	bool Replace,
	bool CallOnEndOnReplace)
{
	FTimerHandle TimerHandle = TimerHandle;

	if (!GetWorld())
	{
		return TimerHandle;
	}

	

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, TickFunction, OnEndFunction, TimerHandle, Duration]()
		{
			float ElapsedTime = 0.f;
			float MaxDuration = Duration;

			if (ElapsedTime >= MaxDuration)
			{
				TickFunction();
				OnEndFunction();
			}
			else
			{
				TickFunction();
				ElapsedTime += 1.f;
			}
		});



	//TimerHandle = GetWorld()->GetTimerManager().SetTimer(TimerHandle, )

	
}
	*/