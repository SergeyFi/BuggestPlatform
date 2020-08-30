// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMaxHealth.h"
#include "BuggestPlatform/Components/Health/HealthComponent.h"

void UItemMaxHealth::OnTargetDetected(AActor* OtherActor)
{
    if (OtherActor)
    {
        auto HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();

        if (HealthComponent)
        {
            HealthComponent->SetMaxHealth(HealthComponent->GetMaxHealth() + MaxHealthAmount);
            HealthComponent->AddDamage(1.0f);
        }
    }
}
