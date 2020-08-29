// Fill out your copyright notice in the Description page of Project Settings.


#include "Detector.h"
#include "Components/ShapeComponent.h"

// Sets default values for this component's properties
UDetector::UDetector()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UDetector::BeginPlay()
{
	Super::BeginPlay();

	BindToOwner();
}

void UDetector::BindToOwner()
{
	if (DetectionShape)
	{
		DetectionShape->OnComponentBeginOverlap.AddDynamic(this, &UDetector::OnShapeOverlap);
	}
}

void UDetector::OnShapeOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OnActorDetected.Broadcast(OtherActor);
}
