// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTak.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(Elevation, 0, 0));
}
