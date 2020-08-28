// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthDelegate, float, Value, AActor*, Instigator);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, IsBlueprintBase="true") )
class BUGGESTPLATFORM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	void AddHealth(float Heal, AActor* Instigator = nullptr);

	void AddDamage(float Damage, AActor* Instigator = nullptr);

	void SetMaxHealth(float MaxHealth);

	FHealthDelegate OnHealthEnded;

	FHealthDelegate OnHealthFull;

	FHealthDelegate OnHealthHealed;

	FHealthDelegate OnHealthDamaged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool HealthRegen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RegenRate;

	void StartHealthRegeneration();

	void StopHealthRegeneration();

	void HealthRegeneration();

	FTimerHandle TimerHealthRegen;
};
