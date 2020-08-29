// Fill out your copyright notice in the Description page of Project Settings.


#include "HealComponent.h"
#include "BuggestPlatform/Components/Health/HealthComponent.h"

void UHealComponent::OnTargetDetected(AActor* OtherActor)
{
    if (OtherActor)
    {
        auto HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();

        if (HealthComponent)
        {
            HealthComponent->AddHealth(HealAmount);
        }
    }
}
