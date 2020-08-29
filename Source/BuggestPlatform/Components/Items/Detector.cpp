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

	AttachDetector();

	BindToOwner();
}

void UDetector::BindToOwner()
{
	if (DetectionShape)
	{
		DetectionShape->OnComponentBeginOverlap.AddDynamic(this, &UDetector::OnShapeOverlap);
	}
}

void UDetector::AttachDetector()
{
	if (DetectionShape)
	{
		DetectionShape->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void UDetector::OnShapeOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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
