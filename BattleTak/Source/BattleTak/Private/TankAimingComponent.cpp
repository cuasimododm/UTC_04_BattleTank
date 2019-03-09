// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO should this realy tick?

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    // So that first fier is after reaload
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    
    return !Barrel->GetForwardVector().Equals(AimDirection, 0.01); // vectors are equals
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel)) { return; }
    
    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
                                                                        OutLaunchVelocity,
                                                                        StartLocation,
                                                                        HitLocation,
                                                                        LaunchSpeed,
                                                                        false,
                                                                        0,
                                                                        0,
                                                                        ESuggestProjVelocityTraceOption::DoNotTrace);
    
    // Calculate the OutLaunchVelocity
    if (bHaveAimSolution)
    {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
        
    }
    // If no solution found do nothing
    
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDir)
{
    if (!ensure(Barrel) || !ensure(Turret)) { return; }
    // Work-out difference between current barrel rotation, and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDir.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(DeltaRotator.Pitch);
    // Always YAW the shortest way
    if (DeltaRotator.Yaw > 180)
        DeltaRotator.Yaw *= -1;
    Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
    if (FiringState != EFiringState::Reloading)
    {
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBlueprint)) { return; }
        
        // Spawn a projectile at the socket location on the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
                                                              Barrel->GetSocketLocation(FName("Projectile")),
                                                              Barrel->GetSocketRotation(FName("Projectile")));
        
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}
