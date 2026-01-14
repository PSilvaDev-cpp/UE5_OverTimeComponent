// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharAttributesStructure.h"	
#include "AttributesMath.h"
#include "CharAttributesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICS01_API UCharAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharAttributesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FCharAttributesStructure Attributes;

	void InitializeAttributes(const FCharAttributesStructure& NewAttributes)
	{
		Attributes = NewAttributes;
	}

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void IncreaseFloatAttribute(float& Attribute, float Value, float Max);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void DecreaseFloatAttribute(float& Attribute, float Value, float Max);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void IncreaseIntAttribute(int32& Attribute, int Value, int32 Max);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void DecreaseIntAttribute(int32& Attribute, int Value, int32 Max);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	FCharAttributesStructure& GetCharAttributes();

};
