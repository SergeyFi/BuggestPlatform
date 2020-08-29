// Fill out your copyright notice in the Description page of Project Settings.


#include "Detector.h"
#include "Components/ShapeComponent.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UDetector::UDetector()
{
	PrimaryComponentTick.bCanEverTick = false;

	OnlyPlayerCanUse = true;
}


// Called when the game starts
void UDetector::BeginPlay()
{
	Super::BeginPlay();

	BindToOwner();
}

void UDetector::BindToOwner()
{
	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UDetector::OnShapeOverlap);
}

void UDetector::OnShapeOverlap(AActor* Owner, AActor* OtherActor)
{
	if (OnlyPlayerCanUse)
	{
		if (!OtherActor->FindComponentByClass<UInputComponent>())
		{
			return;
		}
	}

	OnActorDetected.Broadcast(OtherActor);

	GetOwner()->Destroy();
}
