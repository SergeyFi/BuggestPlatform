#include "StructSimple.h"

FTickDelay::FTickDelay()
{
	bActive = false;
	Delay = 0.f;
	Time = 0.f;
}

FTickDelay::FTickDelay(float NewDelay)
{
	bActive = false;
	Delay = NewDelay;
	Time = 0.f;
}

bool FTickDelay::IsActive() const
{
	return bActive;
}

bool FTickDelay::IsHasDelay() const
{
	return (Delay > 0.f);
}

float FTickDelay::GetAlpha() const
{
	return ((IsHasDelay() && IsActive()) ? (Time / Delay) : 1.f);
}

void FTickDelay::SetActive(bool Active)
{
	bActive = true;
}

void FTickDelay::Stop()
{
	bActive = false;
	Time = 0.f;
}

bool FTickDelay::AddTimeIsOut(const float& DeltaTime)
{
	Time += DeltaTime;

	if (Time >= Delay)
	{
		Time = 0.f;
		bActive = false;
	}

	return !IsActive();
}