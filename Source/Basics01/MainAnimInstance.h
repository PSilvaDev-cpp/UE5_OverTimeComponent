// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainAnimInstance.generated.h"

/**
 */

class UCharacterMovementComponent;

UCLASS()
class BASICS01_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Char")
	AMainCharacter* MainChar;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
	UCharacterMovementComponent* CharMoveComp;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
	float Direction;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
	float Acceleration;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
	bool bIsAccelerating;


	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	

};
