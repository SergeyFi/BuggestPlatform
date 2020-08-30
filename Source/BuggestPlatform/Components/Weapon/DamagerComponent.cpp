// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagerComponent.h"
#include "BuggestPlatform/Components/Health/HealthComponent.h"
#include "GameFramework/Character.h"

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
	GetOwner()->OnActorEndOverlap.AddDynamic(this, &UDamagerComponent::OnOwnerEndOverlap);
	
}

void UDamagerComponent::OnOwnerBeginOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	Target = OtherActor;
	
	ApplyDamage();

	StartDamageLoop();

	if (DestroyOwner)
	{
		GetOwner()->Destroy();
	}
}

void UDamagerComponent::OnOwnerEndOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	StopDamageLoop();
	Target = nullptr;
}

void UDamagerComponent::StartDamageLoop()
{
	if (DamageLoop)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerDamageLoop, this, &UDamagerComponent::ApplyDamage, DamageDelay, true);
	}
}

void UDamagerComponent::StopDamageLoop()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerDamageLoop);
}

void UDamagerComponent::ApplyDamage()
{
	if (Target)
	{
		if (Cast<ACharacter>(Target))
		{
			auto HealthComponent = Target->FindComponentByClass<UHealthComponent>();

			if (HealthComponent)
			{
				HealthComponent->AddDamage(Damage, GetOwner()->GetInstigator());
			}

			OnDamagerImpact.Broadcast(GetOwner());
		}
	}
}
