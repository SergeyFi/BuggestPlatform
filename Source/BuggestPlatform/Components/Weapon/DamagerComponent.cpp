// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagerComponent.h"
#include "BuggestPlatform/Components/Health/HealthComponent.h"

// Sets default values for this component's properties
UDamagerComponent::UDamagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UDamagerComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UDamagerComponent::OnOwnerBeginOverlap);
	
}

void UDamagerComponent::OnOwnerBeginOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	auto HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();

	if (HealthComponent)
	{
		HealthComponent->AddDamage(Damage, GetOwner()->GetInstigator());
	}

	OnDamagerImpact.Broadcast(GetOwner());

	if (DestroyOwner)
	{
		GetOwner()->Destroy();
	}
}
