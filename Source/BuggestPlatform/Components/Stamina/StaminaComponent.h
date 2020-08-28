// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStaminaDelegate, float, Value);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, IsBlueprintBase="true") )
class BUGGESTPLATFORM_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();
	
	void RemoveStamina(float StaminaDamage, bool Silend = false);

	void AddStamina(float StaminaHeal, bool Silent = false);

	float GetStamina();

	void SetMaxStamina(float MaxStamina);

	FStaminaDelegate OnStaminaEnded;

	FStaminaDelegate OnStamindaDamaged;

	FStaminaDelegate OnStaminaAdd;

	FStaminaDelegate OnStaminaFull;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StaminaMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StaminaWasteRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StaminaWasteAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool StaminaRegenNeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StaminaRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StaminaRegenAmount;
	
private:

	class ACharacter* OwnerCharacter;

	void BindMovementComponent();

	UFUNCTION()
	void OnMovementUpdate(class ACharacter* Character, EMovementMode MoveMode, uint8 somedata);

	void StartStaminaWaste();

	void StaminaWaste();

	void StopStaminaWaste();

	void StartStaminaRegen();

	void StaminaRegen();

	void StopStaminaRegen();

	FTimerHandle TimerStaminaWaste;

	FTimerHandle TimerStaminaRegen;
};
