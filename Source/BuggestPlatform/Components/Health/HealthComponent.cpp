// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	HealthMax = 100.0f;

}

void UHealthComponent::AddHealth(float Heal, AActor* Instigator)
{
	Health += Heal;

	if (Health > HealthMax)
	{
		Health = HealthMax;

		OnHealthFull.Broadcast(Health, Instigator);
	}

	OnHealthHealed.Broadcast(Heal, Instigator);
}

void UHealthComponent::AddDamage(float Damage, AActor* Instigator)
{
	Health -= Damage;

	if (Health < 0.0f)
	{
		Health = 0.0f;
	}

	if (FMath::IsNearlyZero(Health))
	{
		OnHealthEnded.Broadcast(Damage, Instigator);
	}

	OnHealthDamaged.Broadcast(Damage, Instigator);

	if (HealthRegen)
	{
		StartHealthRegeneration();
	}
}

void UHealthComponent::SetMaxHealth(float MaxHealth)
{
	HealthMax = MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UHealthComponent::StartHealthRegeneration()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHealthRegen, this,
		&UHealthComponent::HealthRegeneration, RegenRate, true);
}

void UHealthComponent::StopHealthRegeneration()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHealthRegen);
}

void UHealthComponent::HealthRegeneration()
{
	Health += 1.0f * RegenRate;

	if (Health >= HealthMax)
	{
		Health = HealthMax;

		StopHealthRegeneration();
	}
}
