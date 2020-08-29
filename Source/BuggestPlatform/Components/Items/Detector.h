// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Detector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDetectorDelegate, AActor*, OtherActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUGGESTPLATFORM_API UDetector : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDetector();

	UPROPERTY(BlueprintAssignable)
	FDetectorDelegate OnActorDetected;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool OnlyPlayerCanUse;

private:

	void BindToOwner();

	UFUNCTION()
	void OnShapeOverlap(AActor* Owner, AActor* OtherActor);
		
};
