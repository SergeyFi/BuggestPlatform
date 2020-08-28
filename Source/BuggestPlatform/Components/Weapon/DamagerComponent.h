// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamagerImpact, AActor*, Impactor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUGGESTPLATFORM_API UDamagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamagerComponent();

	FDamagerImpact OnDamagerImpact;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	bool DestroyOwner;

	UFUNCTION()
	void OnOwnerBeginOverlap(AActor* OverlapedActor, AActor* OtherActor);
		
};
