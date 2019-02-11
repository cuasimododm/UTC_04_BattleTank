// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximun driving force, and to apply forces to the tank
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETAK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // Sets the throttle between -1 and +1
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);
  
    
    // Max force per track in Newtons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000000; // Asume 40 tonne tank and 1g acceleration
};
