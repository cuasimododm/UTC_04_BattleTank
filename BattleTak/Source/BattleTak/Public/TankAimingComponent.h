// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked
};

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Hold's barrel's properties and elevates barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETAK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();
    
    void AimAt(FVector HitLocation);    

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Aiming;
    
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    void MoveBarrelTowards(FVector AimDirection);
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    /* http://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/ */
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;
    
    double LastFireTime = 0;
};
