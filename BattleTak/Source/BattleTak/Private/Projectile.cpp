// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/EngineTypes.h"

// Sets default values
AProjectile::AProjectile()
{
 	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(true);
    
    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovement->bAutoActivate = false;
    
    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed)
{
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent,
                        AActor* OtherActor,
                        UPrimitiveComponent* OtherComponent,
                        FVector NormalImpulse,
                        const FHitResult& Hit)
{
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
}
