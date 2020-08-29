// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Items/BaseItemComponent.h"
#include "ItemMaxHealth.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUGGESTPLATFORM_API UItemMaxHealth : public UBaseItemComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	float MaxHealthAmount;

	virtual void OnTargetDetected(AActor* OtherActor) override;
};
