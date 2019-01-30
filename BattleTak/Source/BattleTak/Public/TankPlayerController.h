// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETAK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    ATank* GetControlledTank() const;
    
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
private:
    // Starts the tank moving the barrel so that a shot would hit where
    // the crosshair intersects the world
    void AimTowardsCrosshair();
    
    // Return an OUT parameter, true if hit landscape
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
};
