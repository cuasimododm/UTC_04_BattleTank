// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Math/UnrealMathUtility.h"


float ATank::GetHealthPercent() const
{
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), (float)CurrentHealth / (float)StartingHealth);
    return (float)CurrentHealth / (float)StartingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, .0f, CurrentHealth);
    CurrentHealth -= DamageToApply;
    if (CurrentHealth <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank destroyed"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Current Health: %i"), CurrentHealth);
        UE_LOG(LogTemp, Warning, TEXT("Damage Amount: %i"), DamagePoints);
        UE_LOG(LogTemp, Warning, TEXT("Damage To Apply: %i"), DamageToApply);
    }
    
    return DamageToApply;
}

