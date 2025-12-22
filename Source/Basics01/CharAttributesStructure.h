// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharAttributesStructure.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct BASICS01_API FCharAttributesStructure
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 Vitality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 Dexterity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 Intelligence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 Charisma;

	/*
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 BaseVitality;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 BaseStrenght;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 BaseDexteryty;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 BaseIntelligence;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	int32 BaseCharisma;
	*/

	FCharAttributesStructure();

};