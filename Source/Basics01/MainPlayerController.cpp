// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PlayerCharacter.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(GetCharacter());

			if (PlayerChar && PlayerChar->DefaultMappingContext)
			{
				Subsystem->AddMappingContext(PlayerChar->DefaultMappingContext, 0);
			}
		}
	}
}