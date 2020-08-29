#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/StructTarget.h"
#include "EnvInteractionComponent.generated.h"

class UPrimitiveComponent;

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class BUGGESTPLATFORM_API UEnvInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UEnvInteractionComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void InteractionTake(const FHitResult& Hit);

private:
	FBuggestTarget OwnerActor;
	FBuggestTarget CurrentLandTarget;

	void OnLanded(const FHitResult& Hit);
	void OffLanded();
};