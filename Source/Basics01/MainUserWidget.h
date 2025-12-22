// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacter.h"
#include "MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASICS01_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main User Widget")
	AMainCharacter* OwnerCharacter;




	UMainUserWidget(const FObjectInitializer& ObjectInitializer);
	
};
