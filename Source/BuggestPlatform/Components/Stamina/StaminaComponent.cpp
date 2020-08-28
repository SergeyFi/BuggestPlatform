// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	StaminaMax = 100.0f;
}

// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	BindMovementComponent();
}

void UStaminaComponent::RemoveStamina(float StaminaDamage, bool Silent)
{
	Stamina -= StaminaDamage;

	if (Stamina < 0.0f || FMath::IsNearlyZero(Stamina))
	{
		Stamina = 0.0f;

		if (!Silent)
		{
			OnStaminaEnded.Broadcast(Stamina);
		}
	}

	if (StaminaRegenNeed)
	{
		StartStaminaRegen();
	}

	if (!Silent)
	{
		OnStamindaDamaged.Broadcast(StaminaDamage);
	}
	
}

void UStaminaComponent::AddStamina(float StaminaHeal, bool Silent)
{
	Stamina += StaminaHeal;

	if (Stamina > StaminaMax)
	{
		Stamina = StaminaMax;
	}

	if (Stamina == StaminaMax)
	{
		if (!Silent)
		{
			OnStaminaFull.Broadcast(Stamina);
		}
	}

	if (!Silent)
	{
		OnStaminaAdd.Broadcast(StaminaHeal);
	}
}

float UStaminaComponent::GetStamina()
{
	return Stamina;
}

void UStaminaComponent::SetMaxStamina(float MaxStamina)
{
	StaminaMax = MaxStamina;
}

void UStaminaComponent::BindMovementComponent()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	CharacterMovement = OwnerCharacter->GetCharacterMovement();
}

void UStaminaComponent::StartStaminaWaste()
{
	GetWorld()->GetTimerManager().SetTimer(TimerStaminaWaste, this,
		&UStaminaComponent::StaminaWaste,StaminaWasteRate, true);
}

void UStaminaComponent::StaminaWaste()
{
	RemoveStamina((GetOwner()->GetVelocity().Size() * 0.01) * StaminaWasteAmount * StaminaWasteRate, true);
}

void UStaminaComponent::StopStaminaWaste()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerStaminaWaste);
}

void UStaminaComponent::StartStaminaRegen()
{
	GetWorld()->GetTimerManager().SetTimer(TimerStaminaRegen, this,
    &UStaminaComponent::StaminaRegen, StaminaWasteRate, true);
}

void UStaminaComponent::StaminaRegen()
{
	AddStamina(StaminaRegenAmount * StaminaRegenRate, true);

	if (Stamina >= StaminaMax)
	{
		StopStaminaRegen();
	}
}

void UStaminaComponent::StopStaminaRegen()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerStaminaRegen);
}
