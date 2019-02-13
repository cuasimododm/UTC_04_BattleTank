// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETAK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
    
    float AcceptanceRadius = 30;
};
