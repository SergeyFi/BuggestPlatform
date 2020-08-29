// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUGGESTPLATFORM_API UBaseItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnTargetDetected(AActor* OtherActor){};

private:

	UFUNCTION()
	void OnDetection(AActor* OtherActor);
	
		
};
