// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

//Forward declaration
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETAK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    void LaunchProjectile(float Speed);

private:
    UProjectileMovementComponent* ProjectileMovement = nullptr;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CollisionMesh = nullptr;
    
    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* LaunchBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* ImpactBlast = nullptr;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
