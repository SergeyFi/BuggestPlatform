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
	bool DamageLoop;

	UPROPERTY(EditAnywhere)
	float DamageDelay;

	UPROPERTY(EditAnywhere)
	bool DestroyOwner;

	UFUNCTION()
	void OnOwnerBeginOverlap(AActor* OverlapedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOwnerEndOverlap(AActor* OverlapedActor, AActor* OtherActor);

	void StartDamageLoop();

	void StopDamageLoop();

	void ApplyDamage();

	FTimerHandle TimerDamageLoop;

	AActor* Target;
		
};
