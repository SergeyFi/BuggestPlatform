#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/StructTarget.h"
#include "Structs/StructSimple.h"
#include "EnvPlatformComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlatformDelegate, bool, Active);

UENUM(BlueprintType)
enum class EPlatformMoveType : uint8
{
	Direction,
	Spline
};

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class BUGGESTPLATFORM_API UEnvPlatformComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UEnvPlatformComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	bool bMove;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	bool bMoveAutoActive;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	bool bMoveRevert;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MoveDelayEndPos;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	EPlatformMoveType MoveType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveDirection")
	FVector MoveDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveDirection")
	float MoveDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveSpline")
	class USplineComponent* MoveSpline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveSpline")
	bool bMoveSplineSetAbsolute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trampoline")
	bool bTrampoline;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trampoline")
	bool bTrampolineDirectionToMovement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trampoline")
	float TrampolineDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampoline")
	float TrampolineImpulse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trampoline")
	FVector TrampolineDirection;

	UPROPERTY(BlueprintAssignable)
	FPlatformDelegate EventMove;
	UPROPERTY(BlueprintAssignable)
	FPlatformDelegate EventTrampoline;

	UFUNCTION(BlueprintPure, Category = "Move")
	bool IsMoveActive() const;
	UFUNCTION(BlueprintPure, Category = "Move")
	float GetTrampolineDelayAlpha() const;

	UFUNCTION(BlueprintCallable, Category = "Move")
	void SetMove(bool Active);

	void OnLanded(const FBuggestTarget& Target);
	void OffLanded(const FBuggestTarget& Target);
private:
	bool bMoveActive;
	bool bMoveRevertDirection;
	float MoveAlpha;
	FVector MoveDirectionStart;

	FTickDelay MoveDelayTick;
	FTickDelay TrampolineDelayTick;

	TArray<FBuggestTarget> Targets;
	bool IsUseTargets();
	void RemoveTarget(const FBuggestTarget& Target);

	void InternalMoveAlpha(const float& DeltaTime, const float& MoveDist);
	void TrampolineAddImpulse(const FBuggestTarget& Target);
};