// Fill out your copyright notice in the Description page of Project Settings.

#include "Launcher.h"
#include "Actors/ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

ALauncher::ALauncher()
{
    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void ALauncher::PullTrigger()
{
    if (Ammo > 0)
    {
        UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
        UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

        if (ProjectileClass)
        {
            FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
            FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
            AProjectileBase *TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
            TempProjectile->SetOwner(this);
        }

        Ammo = FMath::Max(0, Ammo - 1);
    }
    else
    {
        // Play "empty" sound.
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
    }
}
