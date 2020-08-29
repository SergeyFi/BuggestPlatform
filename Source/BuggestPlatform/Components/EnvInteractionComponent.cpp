#include "EnvInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Environment/EnvPlatformComponent.h"

UEnvInteractionComponent::UEnvInteractionComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;

	OwnerActor = FBuggestTarget();
	CurrentLandTarget = FBuggestTarget();
}

void UEnvInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = FBuggestTarget::Make(GetOwner());
}

void UEnvInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OwnerActor.IsCharacter())
	{
		FFindFloorResult& Floor = OwnerActor.GetCharacterMovement()->CurrentFloor;

		if (!Floor.bWalkableFloor && CurrentLandTarget.IsValidTargetLand())
		{
			OffLanded();
		}
		else if (Floor.bWalkableFloor && (CurrentLandTarget != Floor.HitResult.GetActor()))
		{
			if (CurrentLandTarget.IsValidTargetLand())
			{
				OffLanded();
			}
			OnLanded(Floor.HitResult);
		}
	}
}

void UEnvInteractionComponent::OnLanded(const FHitResult& Hit)
{
	FBuggestTarget Target = FBuggestTarget::Make(Hit);

	if (Target.IsValidTargetLand())
	{
		if (Target.IsValidPlatformComponent())
		{
			Target.GetPlatformComponent()->OnLanded(OwnerActor);

			CurrentLandTarget = Target;
		}
	}
}

void UEnvInteractionComponent::OffLanded()
{
	if (CurrentLandTarget.IsValidTargetLand())
	{
		if (CurrentLandTarget.IsValidPlatformComponent())
		{
			CurrentLandTarget.GetPlatformComponent()->OffLanded(OwnerActor);
		}
	}
	CurrentLandTarget.Clear();
}

void UEnvInteractionComponent::InteractionTake(const FHitResult& Hit)
{
	
}