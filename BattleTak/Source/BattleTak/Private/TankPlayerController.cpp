// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "BattleTak.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    FoundAimingComponent(AimingComponent);
    
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) { return; } // e.g. if not possesing
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    
    FVector HitLocation; // Out parameter
    if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
    {
        AimingComponent->AimAt(HitLocation);        
    }
    
}
// Get world location of linetrace through crosshair
// If it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Find the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    
    // "De-project" the screen position of the crosshair to a world position
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line-trace along that look direction, and see what we hit (up to max range)
        return GetLookVectorHitLocation(LookDirection, OutHitLocation);
        
    }
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarted
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    FHitResult OutHitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(
                                            OutHitResult,
                                            StartLocation,
                                            EndLocation,
                                            ECollisionChannel::ECC_Visibility)
        )
    {
        OutHitLocation = OutHitResult.Location;
        return true;
    }
    
    OutHitLocation = FVector(0);
    return false; // Line trace did'n hit anything
}
