// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharAttributesComponent.h"
#include "DamageInterface.h"
//#include "OverTimeComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GA_SphereScan.h"
#include "MainCharacter.generated.h"



UCLASS()
class BASICS01_API AMainCharacter : public ACharacter, public IDamageInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCharAttributesComponent* CharAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UAbilitySystemComponent* AbilitySystemComponent;
	

public:


	//UPROPERTY(EditDefaultsOnly, Category = "OTCOMPONENT")
	//UOverTimeComponent* OverTimeComponent;

	TMap<FName, FTimerHandle> ActiveTimers;

	virtual void OnTakeDamage_Implementation(float Damage, bool OverTime,
		FName Name,
		bool bAcumulates,
		float Interval,
		float Duration,
		bool Replace) override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void TakeDamage(float Damage);

	void CountDownTimer(FTimerHandle& TimerHandle, float Duration, float Start);

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	void InitializeAbilities();

};
