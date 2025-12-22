// Fill out your copyright notice in the Description page of Project Settings.


#include "CharAttributesComponent.h"

// Sets default values for this component's properties
UCharAttributesComponent::UCharAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCharAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharAttributesComponent::DecreaseFloatAttribute(float& Attribute, float Value, float Min, float Max)
{
	Attribute = AttributesMath::FloatDecreaseValue(Attribute, Value, Min, Max);
}

void UCharAttributesComponent::IncreaseFloatAttribute(float& Attribute, float Value, float Min, float Max)
{
	Attribute = AttributesMath::FloatIncreaseValue(Attribute, Value, Min, Max);
}

void UCharAttributesComponent::DecreaseIntAttribute(int32& Attribute, int Value, int32 Min, int32 Max)
{
	Attribute = AttributesMath::IntDecreaseValue(Attribute, Value, Min, Max);
}

void UCharAttributesComponent::IncreaseIntAttribute(int32& Attribute, int Value, int32 Min, int32 Max)
{
	Attribute = AttributesMath::IntIncreaseValue(Attribute, Value, Min, Max);
}
