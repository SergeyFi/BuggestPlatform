#include "EnvPlatformComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UEnvPlatformComponent::UEnvPlatformComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;

	bMove = false;
	bMoveAutoActive = true;
	bMoveRevert = true;
	MoveDelayEndPos = 0.f;
	MoveType = EPlatformMoveType::Direction;
	MoveSpeed = 500.f;

	MoveDirection = FVector::ForwardVector;
	MoveDistance = 1000.f;

	MoveSpline = nullptr;
	bMoveSplineSetAbsolute = false;

	bTrampoline = false;
	bTrampolineDirectionToMovement = false;
	TrampolineDelay = 0.f;
	TrampolineImpulse = 1000.f;
	TrampolineDirection = FVector::UpVector;

	bMoveActive = false;
	bMoveRevertDirection = true;
	MoveAlpha = 0.f;

	MoveDelayTick = FTickDelay();
	TrampolineDelayTick = FTickDelay();
}

bool UEnvPlatformComponent::IsUseTargets()
{
	return (bTrampoline /*|| bSeesaw*/);
}

void UEnvPlatformComponent::BeginPlay()
{
	Super::BeginPlay();

	MoveDelayTick = FTickDelay(MoveDelayEndPos);
	TrampolineDelayTick = FTickDelay(TrampolineDelay);

	if (bMove)
	{
		if (MoveType == EPlatformMoveType::Direction)
		{
			MoveDirectionStart = GetOwner()->GetActorLocation();
		}

		if (bMoveSplineSetAbsolute && MoveSpline)
		{
			MoveSpline->SetAbsolute(true, true, true);
			MoveSpline->SetWorldLocationAndRotation(GetOwner()->GetActorLocation(), GetOwner()->GetActorQuat());
		}

		if (bMoveAutoActive)
		{
			SetMove(true);
		}
	}
}

void UEnvPlatformComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bMoveActive)
	{
		if (MoveDelayTick.IsActive())
		{
			if (MoveDelayTick.AddTimeIsOut(DeltaTime))
			{
				EventMove.Broadcast(true);
			}
		}

		if (!MoveDelayTick.IsActive())
		{
			if (MoveType == EPlatformMoveType::Direction)
			{
				InternalMoveAlpha(DeltaTime, MoveDistance);

				FVector NewLoc = (MoveDirectionStart + MoveDirection*MoveDistance*MoveAlpha);

				GetOwner()->SetActorLocation(NewLoc);
			} 
			else
			{
				InternalMoveAlpha(DeltaTime, MoveSpline->GetSplineLength());

				FVector NewLoc = MoveSpline->GetWorldLocationAtTime(MoveAlpha, true);

				GetOwner()->SetActorLocation(NewLoc);
			}	
		}
	}

	if (bTrampoline && TrampolineDelayTick.IsActive())
	{
		if (TrampolineDelayTick.AddTimeIsOut(DeltaTime))
		{
			for (const FBuggestTarget& Target : Targets)
			{
				TrampolineAddImpulse(Target);
			}

			EventTrampoline.Broadcast(false);
		}
	}
}

void UEnvPlatformComponent::OnLanded(const FBuggestTarget& Target)
{
	if (IsUseTargets() && Target.IsValidTarget())
	{
		Targets.Add(Target);

		if (bTrampoline)
		{
			if (TrampolineDelayTick.IsHasDelay())
			{
				TrampolineDelayTick.SetActive();
				EventTrampoline.Broadcast(true);
			} 
			else
			{
				TrampolineAddImpulse(Target);
			}
		}
	}
}

void UEnvPlatformComponent::OffLanded(const FBuggestTarget& Target)
{
	if (IsUseTargets() && Target.IsValidTarget())
	{
		RemoveTarget(Target);

		if (bTrampoline && TrampolineDelayTick.IsActive() && (Targets.Num() == 0))
		{
			TrampolineDelayTick.Stop();
			EventTrampoline.Broadcast(false);
		}
	}
}

void UEnvPlatformComponent::RemoveTarget(const FBuggestTarget& Target)
{
	for (int32 i = 0; i < Targets.Num(); i++)
	{
		if (Targets[i] == Target)
		{
			Targets.RemoveAtSwap(i);
			break;
		}
	}
}

bool UEnvPlatformComponent::IsMoveActive() const
{
	return bMoveActive;
}

float UEnvPlatformComponent::GetTrampolineDelayAlpha() const
{
	return TrampolineDelayTick.GetAlpha();
}

void UEnvPlatformComponent::SetMove(bool Active)
{
	if (bMove && (bMoveActive != Active))
	{
		bMoveActive = Active;

		EventMove.Broadcast(bMoveActive);
	}
}

void UEnvPlatformComponent::InternalMoveAlpha(const float& DeltaTime, const float& MoveDist)
{
	float NewDistance = (MoveAlpha * MoveDist + MoveSpeed * DeltaTime * (bMoveRevertDirection ? 1.f : -1.f));
	bool NewDistUpMax = (NewDistance >= MoveDist);

	if (NewDistUpMax || (NewDistance <= 0.f))
	{
		if (MoveDelayTick.IsHasDelay())
		{
			NewDistance = (NewDistUpMax ? MoveDist : 0.f);
			MoveDelayTick.SetActive();
			EventMove.Broadcast(false);
		}
		else
		{
			NewDistance = (NewDistUpMax ? (MoveDist - (NewDistance - MoveDist)) : (-1.f * NewDistance));
		}
		bMoveRevertDirection = !bMoveRevertDirection;
	}

	MoveAlpha = (NewDistance / MoveDist);
	MoveAlpha = FMath::Clamp(MoveAlpha, 0.f, 1.f);

	if (!bMoveRevert)
	{
		SetMove(false);
	}
}

void UEnvPlatformComponent::TrampolineAddImpulse(const FBuggestTarget& Target)
{
	UCharacterMovementComponent* MovComp = Target.GetCharacterMovement();

	if (MovComp)
	{
		FVector Direction = TrampolineDirection;

		if (bTrampolineDirectionToMovement)
		{
			FVector Vel = Target.Target->GetVelocity();
			Vel.Z = 0;
			Vel.Normalize();
			Direction += Vel;
		}

		MovComp->AddImpulse((Direction * TrampolineImpulse), true);
	}
}