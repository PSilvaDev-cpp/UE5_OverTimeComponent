// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;

UCLASS()
class BASICS01_API APlayerCharacter : public AMainCharacter
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	UInputAction* IA_Sprint;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	bool bIsSprinting;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void OnStartJump(const FInputActionValue& Value);
	void OnStopJump(const FInputActionValue& Value);

	void OnStartSprint(const FInputActionValue& Value);
	void OnStopSprint(const FInputActionValue& Value);

};
