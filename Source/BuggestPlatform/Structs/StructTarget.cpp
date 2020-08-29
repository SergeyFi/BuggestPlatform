#include "StructTarget.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Environment/EnvPlatformComponent.h"

FBuggestTarget::FBuggestTarget()
{
	ClearPure();
}

FBuggestTarget FBuggestTarget::Make(AActor* TargetActor, UPrimitiveComponent* TargetComponent)
{
	FBuggestTarget NewTarget = FBuggestTarget();
	NewTarget.ClearPure();
	NewTarget.Target = TargetActor;
	NewTarget.TargetComp = TargetComponent;
	NewTarget.Init();
	return NewTarget;
}

FBuggestTarget FBuggestTarget::Make(const FHitResult& Hit)
{
	return FBuggestTarget::Make(Hit.GetActor(), Hit.GetComponent());
}

FBuggestTarget& FBuggestTarget::operator=(const FBuggestTarget& BuggestTarget)
{
	this->ClearPure();
	this->Target = BuggestTarget.Target;
	this->TargetComp = BuggestTarget.TargetComp;
	this->Init();

	return *this;
}

bool FBuggestTarget::operator==(const AActor* TargetActor) const
{
	return (Target == TargetActor);
}

bool FBuggestTarget::operator==(const FBuggestTarget& BuggestTarget) const
{
	return (BuggestTarget == Target);
}

bool FBuggestTarget::operator!=(const AActor* TargetActor) const
{
	return (Target != TargetActor);
}

bool FBuggestTarget::IsValidTarget() const
{
	return (Target != nullptr);
}

bool FBuggestTarget::IsCharacter() const
{
	return (Character != nullptr);
}

bool FBuggestTarget::IsValidTargetLand() const
{
	return (IsValidTarget() && IsValidPlatformComponent());
}

bool FBuggestTarget::IsValidPlatformComponent() const
{
	return (PlatformComp != nullptr);
}

ACharacter* FBuggestTarget::GetCharacter() const
{
	return Character;
}

UCharacterMovementComponent* FBuggestTarget::GetCharacterMovement() const
{
	return (Character ? Character->GetCharacterMovement() : nullptr);
}

UEnvPlatformComponent* FBuggestTarget::GetPlatformComponent() const
{
	return PlatformComp;
}

float FBuggestTarget::GetWeight() const
{
	return 100.f;
}

void FBuggestTarget::Init()
{
	if (Target)
	{
		Character = Cast<ACharacter>(Target);

		if (!TargetComp)
		{
			TargetComp = Cast<UPrimitiveComponent>(Target->GetRootComponent());
		}

		PlatformComp = Target->FindComponentByClass<UEnvPlatformComponent>();
	}
}

void FBuggestTarget::ClearPure()
{
	Target = nullptr;
	Character = nullptr;
	TargetComp = nullptr;
	PlatformComp = nullptr;
}

void FBuggestTarget::Clear()
{
	ClearPure();
}