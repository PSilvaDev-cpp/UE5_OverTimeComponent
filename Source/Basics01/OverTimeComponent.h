// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OverTimeComponent.generated.h"


USTRUCT()
struct FOverTimeInstance
{
	GENERATED_BODY()

public:

	int32 InstanceID = -1;
	FName Name = NAME_None;
	bool bAccumulating = true;
	int32 CallsPerInterval = 1;
	float IntervalSeconds = 1.0f;
	float DurationSeconds = 0.0f;
	float TimePassed = 0.0f;
	TFunction<void()> TickFunction;
	TFunction<void()> FinishFunction;
	FTimerHandle TimerHandle;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICS01_API UOverTimeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOverTimeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	TMap<FName, TArray<FOverTimeInstance>> ActiveTimers;
	int32 NextInstanceID = 1;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool FindInstance(int32 InstanceID, FName& OutName, int32& OutIndex);

	void RemoveInstanceByID(int32 InstanceID);

	bool CheckAndResolveExistingTimers(FName TimerName, bool bAccumulating, bool bReaplaceIfExists, bool bCallFinishOnReplace);

	int32 StartOverTime(FName TimerName, bool bAccumulating, int32 CallsPerInterval, float IntervalSeconds, float DurationSeconds,
		TFunction<void()> TickFunction, TFunction<void()> FinishFunction, bool bReplaceIfExists = true, bool bCallFinishOnReplace = false);

	void ExecuteInstanceTick(int32 InstanceID);

	bool StopOverTimeByID(int32 InstanceID, bool bCallFinish);

	int32 StopOverTimeByName(FName TimerName, bool bCallFinish);

	bool HasActiveTimerWithName(FName TimerName) const;

	void GetActiveInstanceIDs(FName TimerName, TArray<int32>& OutInstanceIDs) const;

};
