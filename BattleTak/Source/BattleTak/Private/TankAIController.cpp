// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTak.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("IAController not possessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("IAController possesing: %s"), *(ControlledTank->GetName()));
    }
    
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("IAController haven't found player's tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("IAController have found player's tank: %s"), *(PlayerTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerTank) { return nullptr; }
    
    return Cast<ATank>(PlayerTank);
    
}

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick( DeltaSeconds );
    
    if (GetPlayerTank())
    {
        // TODO Move towards the player
        
        // Aim towards the player
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
        
        // Fire if it's ready
        
    }
}
