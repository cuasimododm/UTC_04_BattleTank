// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETAK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // -1 is max CCW speed, and +1 is max CW movement
    void Rotate(float RelativeSpeed);
    
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSeconds = 25;
};
