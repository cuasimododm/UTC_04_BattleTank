// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank; // Forward declaration
/**
 * 
 */
UCLASS()
class BATTLETAK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    ATank* GetControlledTank() const;
    
private:
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Starts the tank moving the barrel so that a shot would hit where
    // the crosshair intersects the world
    void AimTowardsCrosshair();
    
    // Return an OUT parameter, true if hit landscape
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.3333;
    
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.0;
};
