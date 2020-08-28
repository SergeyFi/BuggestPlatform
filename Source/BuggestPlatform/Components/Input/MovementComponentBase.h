// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "MovementComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUGGESTPLATFORM_API UMovementComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UInputComponent* InputComponent;

	UPROPERTY()
	ACharacter* PlayerCharacter;

	void FindInputComponent();

	void BindToInputComponent();

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);
		
};
