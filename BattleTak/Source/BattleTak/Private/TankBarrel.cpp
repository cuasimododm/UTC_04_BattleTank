// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTak.h"

void UTankBarrel::Elevate(float DegreesPerSeconds)
{
    UE_LOG(LogTemp, Warning, TEXT("Barrel elevate at %f speed"), DegreesPerSeconds);
}
