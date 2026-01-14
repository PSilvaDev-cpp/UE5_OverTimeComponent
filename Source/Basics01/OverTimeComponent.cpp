// Fill out your copyright notice in the Description page of Project Settings.


#include "OverTimeComponent.h"


// Sets default values for this component's properties
UOverTimeComponent::UOverTimeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UOverTimeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOverTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}




void UOverTimeComponent::StartOverTimeFunction(
		FName Name,
		bool bAcumulates,
		float Interval,
		float Duration,
		TFunction<void()> TickFunction,
		TFunction<void()> OnEndFunction,
		bool Replace
	)
{
	FTimerHandle TimerHandle;

	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("GetWorld() Invalid"));
		return;
	}

	float StartTime = GetWorld()->GetTimeSeconds();

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, TickFunction, OnEndFunction, Duration, StartTime, TimerHandle]() mutable	
		{
			if (GetWorld()->GetTimeSeconds() - StartTime >= Duration )
			{
				TickFunction();
				OnEndFunction();
				if (TimerHandle.IsValid())
				{
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				}
			}
			else
			{
				TickFunction();
			}
		});

	if (Timers.Find(Name))
	{
		if (bAcumulates)
		{
				
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Interval, true);
			Timers[Name].Add(TimerHandle);
			
		}
		else
		{
			// Timers[Name] -> Restart Timer ... maybe set ElapsedTime to 0...
			

		}
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Interval, true);
	Timers[Name].Add(TimerHandle);
	return;
}