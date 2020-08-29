#pragma once

#include "CoreMinimal.h"
#include "StructTarget.generated.h"

class AActor;
class ACharacter;
class UCharacterMovementComponent;
class UPrimitiveComponent;
class UEnvPlatformComponent;

USTRUCT(BlueprintType)
struct FBuggestTarget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target;

	FBuggestTarget();
	static FBuggestTarget Make(AActor* TargetActor, UPrimitiveComponent* TargetComponent = nullptr);
	static FBuggestTarget Make(const FHitResult& Hit);

	FBuggestTarget& operator=(const FBuggestTarget& BuggestTarget);
	bool operator==(const AActor* TargetActor) const;
	bool operator==(const FBuggestTarget& BuggestTarget) const;
	bool operator!=(const AActor* TargetActor) const;

	bool IsValidTarget() const;
	bool IsCharacter() const;
	bool IsValidTargetLand() const;
	bool IsValidPlatformComponent() const;

	ACharacter* GetCharacter() const;
	UCharacterMovementComponent* GetCharacterMovement() const;
	UEnvPlatformComponent* GetPlatformComponent() const;

	float GetWeight() const;

	void Clear();	
private:
	ACharacter* Character;
	UPrimitiveComponent* TargetComp;
	UEnvPlatformComponent* PlatformComp;

	void Init();
	void ClearPure();
};