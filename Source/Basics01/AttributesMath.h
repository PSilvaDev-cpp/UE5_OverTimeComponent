// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "math.h"
#include "CoreMinimal.h"

/**
 * 
 */
class BASICS01_API AttributesMath
{
public:
	
public:

	static float FloatDecreaseValue(float OriginValue, float Value, float Min, float Max);
	static float FloatIncreaseValue(float OriginValue, float Value, float Min, float Max);

	static int32 IntDecreaseValue(int32 OriginValue, int32 Value, int32 Min, int32 Max);
	static int32 IntIncreaseValue(int32 OriginValue, int32 Value, int32 Min, int32 Max);
};
