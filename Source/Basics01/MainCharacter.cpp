// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"


class UCharAttributesComponent;

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CharAttributes = CreateDefaultSubobject<UCharAttributesComponent>(TEXT("CharAttributes"));
	OverTimeComponent = CreateDefaultSubobject<UOverTimeComponent>(TEXT("OverTimeComponent"));

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
//	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainCharacter::OnTakeDamage_Implementation(float DamageAmount, bool OverTime, float Duration)
{
	UE_LOG(LogTemp, Warning, TEXT("Take Damage Called"));

	if (!CharAttributes) { return; }

	UE_LOG(LogTemp, Warning, TEXT("CharAttributeIsValid"));

	if (OverTime && OverTimeComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("OTDamage"));

		int32 TimerID = OverTimeComponent->StartOverTime(
			TEXT("DamageOverTime"),
			false,
			1,
			1.0f,
			Duration,
			[this, DamageAmount]()
			{
				CharAttributes->DecreaseFloatAttribute(CharAttributes->Attributes.Health, DamageAmount, 0.f, CharAttributes->Attributes.MaxHealth);
			},
			nullptr,
			true,
			false
		);

		if(TimerID != -1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Started DoT with ID: %d"), TimerID);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to start DoT"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SingleDamage"));
		CharAttributes->DecreaseFloatAttribute(CharAttributes->Attributes.Health, DamageAmount, 0.f, CharAttributes->Attributes.MaxHealth);
	}

}


