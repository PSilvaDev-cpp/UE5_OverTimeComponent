// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

class UCharAttributesComponent;
class UAbilitySystemComponent;

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CharAttributes = CreateDefaultSubobject<UCharAttributesComponent>(TEXT("CharAttributes"));
	//OverTimeComponent = CreateDefaultSubobject<UOverTimeComponent>(TEXT("OverTimeComponent"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

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

void AMainCharacter::TakeDamage(float Damage)
{
	CharAttributes->DecreaseFloatAttribute(CharAttributes->GetCharAttributes().Health, Damage, CharAttributes->GetCharAttributes().MaxHealth);
}

void AMainCharacter::CountDownTimer(FTimerHandle& TimerHandle, float Duration, float Start)
{
	if (!GetWorld())
	{
		return;
	}
	float ElapsedTime = GetWorld()->GetTimeSeconds() - Start;
	if(ElapsedTime >= Duration)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		return;
	}
}

void AMainCharacter::OnTakeDamage_Implementation(float Damage, bool OverTime,
	FName Name,
	bool bAcumulates,
	float Interval,
	float Duration,
	bool Replace)
{

	float StartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
	float ElapsedTime = 0.f;

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, Damage, Name, Duration, StartTime]()
		{
			TakeDamage(Damage);
			CountDownTimer(ActiveTimers[Name], Duration, StartTime);
		});
	FTimerHandle TimerHandle;

	if (!IsValid(this) or !CharAttributes or !GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("On Take Damage Called but FAILED"));
		return;
	}
	
	if (OverTime)
	{
		if(ActiveTimers.Contains(Name))
		{	
			if (FTimerHandle* FoundHandle = ActiveTimers.Find(Name))
			{
				GetWorld()->GetTimerManager().ClearTimer(*FoundHandle);
			}
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				TimerDelegate,
				1.f,
				true);
			ActiveTimers.Add(Name, TimerHandle);
		}
		else
		{
			TakeDamage(Damage);
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				TimerDelegate,
				1.f,
				true);		
			ActiveTimers.Add(Name, TimerHandle);
		}
	}
	else
	{
		TakeDamage(Damage);
	}
}



void AMainCharacter::InitializeAbilities()
{
	if(!HasAuthority() || !AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UGA_SphereScan::StaticClass(), 1, 0));

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

}

void AMainCharacter::OnRep_PlayerState()
{
	if(AbilitySystemComponent)
	{
		InitializeAbilities();
	}
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(AbilitySystemComponent)
	{
		InitializeAbilities();
	}
}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMainCharacter::ActiveSkill(TSubclassOf<UGA_AbilityBase> AbilityClass) 
{
	if (!AbilitySystemComponent || !AbilityClass) { return; }
	{
		AbilitySystemComponent->TryActivateAbilityByClass(AbilityClass);
	}
}
