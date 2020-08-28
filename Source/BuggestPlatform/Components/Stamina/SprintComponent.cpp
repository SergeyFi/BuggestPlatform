// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
USprintComponent::USprintComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WalkMode = FWalkMode::Walk;

	ActionName = "Sprint";
}

FWalkMode USprintComponent::GetWalkMode()
{
	return WalkMode;
}

void USprintComponent::BlockSprint()
{
	SprintIsBlocked = true;
	SetWalkMode();
}

void USprintComponent::UnblockSprint()
{
	SprintIsBlocked = false;
}

// Called when the game starts
void USprintComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterMovement = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();

	BindToInput();
}

void USprintComponent::SetSprintMode()
{
	if (!SprintIsBlocked)
	{
		WalkMode = FWalkMode::Sprint;

		OnWalkModeChange.Broadcast(WalkMode);

		if (CharacterMovement)
		{
			CharacterMovement->MaxWalkSpeed = SprintSpeed;
		}
	}
}

void USprintComponent::SetWalkMode()
{
	WalkMode = FWalkMode::Walk;
	
	OnWalkModeChange.Broadcast(WalkMode);

	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = WalkSpeed;
	}
}

void USprintComponent::BindToInput()
{
	auto InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction(ActionName, IE_Pressed, this, &USprintComponent::SetSprintMode);
		InputComponent->BindAction(ActionName, IE_Released, this, &USprintComponent::SetWalkMode);
	}
}
