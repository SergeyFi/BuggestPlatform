// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Items/BaseItemComponent.h"
#include "HealComponent.generated.h"

UCLASS()
class BUGGESTPLATFORM_API UHealComponent : public UBaseItemComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	float HealAmount;

	virtual void OnTargetDetected(AActor* OtherActor) override;
	
};
