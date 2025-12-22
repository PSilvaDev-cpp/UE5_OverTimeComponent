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


void UOverTimeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto& Pair : ActiveTimers)
	{
		for (FOverTimeInstance& Inst : Pair.Value)
		{
			if (Inst.TimerHandle.IsValid())
			{
				if(GetWorld())
				{
					GetWorld()->GetTimerManager().ClearTimer(Inst.TimerHandle);
				}
			}
		}
	}
	ActiveTimers.Reset();
	Super::EndPlay(EndPlayReason);
}

bool UOverTimeComponent::FindInstance(int32 InstanceID, FName& OutName, int32& OutIndex)
{
	for (auto& Pair : ActiveTimers)
	{
		const FName& Name = Pair.Key;
		TArray<FOverTimeInstance>& Arr = Pair.Value;
		
		for(int32 i = 0; i < Arr.Num(); ++i)
			if(Arr[i].InstanceID == InstanceID)
			{
				OutName = Name;
				OutIndex = i;
				return true;
			}
	}
	return false;
}

void UOverTimeComponent::RemoveInstanceByID(int32 InstanceID)
{
	FName Name;
	int32 Index = -1;

	if (!FindInstance(InstanceID, Name, Index))
	{
		return;
	}
	
	TArray<FOverTimeInstance>& Arr = ActiveTimers.FindOrAdd(Name);

	if (Arr.IsValidIndex(Index))
	{
		Arr.RemoveAt(Index);
	}

	if(Arr.Num() == 0)
	{
		ActiveTimers.Remove(Name);
	}

}

bool UOverTimeComponent::CheckAndResolveExistingTimers(FName TimerName, bool bAccumulating, bool bReplaceIfExists, bool bCallFinishOnReplace)
{
	if(bAccumulating)
	{
		return false;
	}
	
	TArray<FOverTimeInstance>* ExistingArr = ActiveTimers.Find(TimerName);

	if (!ExistingArr || ExistingArr->Num() == 0)
	{
		return true;
	}

	if (!bReplaceIfExists)
	{
		return false;
	}

	for (FOverTimeInstance& Old : *ExistingArr)
	{
		if (!Old.TimerHandle.IsValid() && GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(Old.TimerHandle);
		}
		if(bCallFinishOnReplace && Old.FinishFunction)
		{
			Old.FinishFunction();
		}
	}

	ActiveTimers.Remove(TimerName);
	return true;
}

int32 UOverTimeComponent::StartOverTime(FName TimerName, bool bAccumulating, int32 CallsPerInterval, float IntervalSeconds, float DurationSeconds,
	TFunction<void()>TickFunction, TFunction<void()>FinishFunction, bool bReplaceIfExists, bool bCallFinishOnReplace)
{
	if (!GetWorld())
	{
		return -1;
	}
	if (CallsPerInterval <= 0)
	{
		CallsPerInterval = 1;
	}
	if (IntervalSeconds <= 0.f)
	{
		IntervalSeconds = 1.f;
	}
	if (!CheckAndResolveExistingTimers(TimerName, bAccumulating, bReplaceIfExists, bCallFinishOnReplace))
	{
		return -1;
	}

	FOverTimeInstance NewInst;
	NewInst.InstanceID = NextInstanceID++;
	NewInst.Name = TimerName;
	NewInst.bAccumulating = bAccumulating;
	NewInst.CallsPerInterval = CallsPerInterval;
	NewInst.IntervalSeconds = IntervalSeconds;
	NewInst.DurationSeconds = DurationSeconds;
	NewInst.TimePassed = 0.f;
	NewInst.TickFunction = MoveTemp(TickFunction);
	NewInst.FinishFunction = MoveTemp(FinishFunction);

	TWeakObjectPtr<UOverTimeComponent> WeakThis(this);
	int32 MyInstanceID = NewInst.InstanceID;

	FTimerDelegate TimerDel;

	TimerDel.BindLambda([WeakThis, MyInstanceID]()
		{
			if (!WeakThis.IsValid())
			{
				return;
			}
			UOverTimeComponent* Comp = WeakThis.Get();
			Comp->ExecuteInstanceTick(MyInstanceID);
		}
	);
	GetWorld()->GetTimerManager().SetTimer(NewInst.TimerHandle, TimerDel, IntervalSeconds, true);
	TArray<FOverTimeInstance>& Arr = ActiveTimers.FindOrAdd(TimerName);
	Arr.Add(MoveTemp(NewInst));
	return Arr.Last().InstanceID;
}

void UOverTimeComponent::ExecuteInstanceTick(int32 InstanceID)
{
	FName Name;
	int32 Index;

	if(!FindInstance(InstanceID, Name, Index))
	{
		return;
	}
	
	TArray<FOverTimeInstance>& Arr = ActiveTimers.FindOrAdd(Name);

	if (!Arr.IsValidIndex(Index))
	{
		return;
	}

	FOverTimeInstance& Inst = Arr[Index];

	for(int32 i = 0; i < Inst.CallsPerInterval; ++i)
	{
		if (Inst.TickFunction)
		{
			Inst.TickFunction();
		}
	}
	if (Inst.DurationSeconds > 0.f)
	{
		Inst.TimePassed += Inst.IntervalSeconds;

		if (Inst.TimePassed >= Inst.DurationSeconds)
		{
			if (Inst.FinishFunction)
			{
				Inst.FinishFunction();
			}
		}
		if(Inst.TimerHandle.IsValid() && GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(Inst.TimerHandle);
		}
		RemoveInstanceByID(InstanceID);
		return;
	}
}

bool UOverTimeComponent::StopOverTimeByID(int32 InstanceID, bool bCallFinish)
{
	FName Name;
	int32 Index;

	if(!FindInstance(InstanceID, Name, Index))
	{
		return false;
	}
	
	TArray<FOverTimeInstance>& Arr = ActiveTimers.FindOrAdd(Name);

	if (!Arr.IsValidIndex(Index))
	{
		return false;
	}

	FOverTimeInstance& Inst = Arr[Index];

	if(Inst.TimerHandle.IsValid() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(Inst.TimerHandle);
	}

	RemoveInstanceByID(InstanceID);

	if(bCallFinish && Inst.FinishFunction)
	{
		Inst.FinishFunction();
	}

	return true;
}

int32 UOverTimeComponent::StopOverTimeByName(FName TimerName, bool bCallFinish)
{
	TArray<FOverTimeInstance>* ArrPtr = ActiveTimers.Find(TimerName);

	if(!ArrPtr || ArrPtr->Num() == 0)
	{
		return 0;
	}
	
	TArray<int32> IDs;

	for (const FOverTimeInstance& I : *ArrPtr)
	{
		IDs.Add(I.InstanceID);
	}

	int32 Stopped = 0;

	for (int32 ID : IDs)
	{
		if(StopOverTimeByID(ID, bCallFinish))
		{
			++Stopped;
		}
	}
	return Stopped;
}

bool UOverTimeComponent::HasActiveTimerWithName(FName TimerName) const
{
	const TArray<FOverTimeInstance>* Arr = ActiveTimers.Find(TimerName);
	return Arr && Arr->Num() > 0;
}

void UOverTimeComponent::GetActiveInstanceIDs(FName TimerName, TArray<int32>& OutInstanceIDs) const
{
	OutInstanceIDs.Empty();
	const TArray<FOverTimeInstance>* Arr = ActiveTimers.Find(TimerName);

	if (!Arr)
	{
		return;
	}
	for (const FOverTimeInstance& I : *Arr)
	{
		OutInstanceIDs.Add(I.InstanceID);
	}
}