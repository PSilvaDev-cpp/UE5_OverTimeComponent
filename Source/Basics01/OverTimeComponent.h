// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"

#include "OverTimeComponent.generated.h"
/*
USTRUCT(BlueprintType)
struct FOverTimeInstance
{
	GENERATED_BODY()

public:

	FName Name;
	FTimerHandle THandle;
	float ElapsedTime;
	float Duration;
	float StartTime;

};
*/

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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OT")
	TMap<FName, TArray<FTimerHandle>> Timers;

	
	void StartOverTimeFunction(
		FName Name,
		bool bAcumulates,
		float Interval,
		float Duration,
		TFunction<void()> TickFunction,
		TFunction<void()> OnEndFunction,
		bool Replace
	);


};
