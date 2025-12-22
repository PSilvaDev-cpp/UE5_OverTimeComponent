// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(!IsValid(MainChar = Cast<AMainCharacter>(TryGetPawnOwner())))
	{
		return;
	}

	CharMoveComp = MainChar->GetCharacterMovement();
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}


void UMainAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(MainChar == nullptr || !CharMoveComp)
	{
		return;
	}

	Velocity = CharMoveComp->Velocity;
	Speed = Velocity.Size2D();
	Rotation = MainChar->GetActorRotation();
	Direction = CalculateDirection(Velocity, Rotation);
	Acceleration = CharMoveComp->GetCurrentAcceleration().Size();
	bIsInAir = CharMoveComp->IsFalling();
	bIsAccelerating = CharMoveComp->GetCurrentAcceleration().Size() > 0.f;

}