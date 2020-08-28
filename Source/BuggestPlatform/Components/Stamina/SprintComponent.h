// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SprintComponent.generated.h"

UENUM(BlueprintType)
enum class FWalkMode : uint8
{
	Walk UMETA(DisplayName = "Walk"),
	Sprint UMETA(DisplayName = "Sprint")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSprintDelegate, FWalkMode, WalkMode);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, IsBlueprintBase="true") )
class BUGGESTPLATFORM_API USprintComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintComponent();

	FWalkMode GetWalkMode();

	FSprintDelegate OnWalkModeChange;

	UFUNCTION(BlueprintCallable)
	void BlockSprint();

	UFUNCTION(BlueprintCallable)
	void UnblockSprint();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float WalkSpeed;

	UPROPERTY(EditAnywhere)
	float SprintSpeed;

	UPROPERTY(EditAnywhere)
	FName ActionName;

	bool SprintIsBlocked;

	FWalkMode WalkMode;

	void InvertWalkMode();

	void SetSprintMode();

	void SetWalkMode();

	void BindToInput();

	class UCharacterMovementComponent* CharacterMovement;
		
};
