// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesMath.h"

float AttributesMath::FloatDecreaseValue(float OriginValue, float Value, float Min, float Max)
{
	return FMath::Clamp(OriginValue - Value, Min, Max);
}

float AttributesMath::FloatIncreaseValue(float OriginValue, float Value, float Min, float Max)
{
	return FMath::Clamp(OriginValue + Value, Min, Max);
}

int32 AttributesMath::IntDecreaseValue(int32 OriginValue, int32 Value, int32 Min, int32 Max)
{
	return FMath::Clamp(OriginValue - Value, (int32)Min, (int32)Max);
}

int32 AttributesMath::IntIncreaseValue(int32 OriginValue, int32 Value, int32 Min, int32 Max)
{
	return FMath::Clamp(OriginValue + Value, (int32)Min, (int32)Max);
}