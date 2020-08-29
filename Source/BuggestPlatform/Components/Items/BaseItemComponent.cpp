// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemComponent.h"
#include "BuggestPlatform/Components/Items/Detector.h"

// Sets default values for this component's properties
UBaseItemComponent::UBaseItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UBaseItemComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Detector = GetOwner()->FindComponentByClass<UDetector>();

	if (Detector)
	{
		Detector->OnActorDetected.AddDynamic(this, &UBaseItemComponent::OnDetection);
	}

}

void UBaseItemComponent::OnDetection(AActor* OtherActor)
{
	OnTargetDetected(OtherActor);
}
