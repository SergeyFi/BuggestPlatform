#pragma once

#include "CoreMinimal.h"
#include "StructSimple.generated.h"

USTRUCT()
struct FTickDelay
{
	GENERATED_BODY()
public:
	FTickDelay();
	FTickDelay(float NewDelay);

	bool IsActive() const;
	bool IsHasDelay() const;
	float GetAlpha() const;

	void SetActive(bool Active = true);
	void Stop();
	bool AddTimeIsOut(const float& DeltaTime);
private:
	bool bActive;
	float Delay;
	float Time;
};