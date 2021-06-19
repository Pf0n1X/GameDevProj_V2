// Fill out your copyright notice in the Description page of Project Settings.

#include "Loot.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

// Sets default values
ALoot::ALoot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ALoot::OnOverlapBegin); 
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ALoot::OnOverlapEnd); 
	TriggerCapsule->SetupAttachment(Root);

	// Add the ParticleSystem
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ALoot::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALoot::OnOverlapBegin(UPrimitiveComponent *OverlappedComponent,
						 AActor *OtherActor,
						 UPrimitiveComponent *OtherComp,
						 int32 OtherBodyIndex,
						 bool bFromSweep,
						 const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision"));
	// Play the pickup particle system
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupParticles, GetActorLocation());

	// Play Sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());

	// Give Ammo to player
	AShooterCharacter * ShooterCharacter = Cast<AShooterCharacter>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("T1"));
	if (ShooterCharacter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("T2"));
		ShooterCharacter->FillActiveGunAmmo();
	}

	// Destroy Actor
	Destroy();
}

void ALoot::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
					  class AActor *OtherActor,
					  class UPrimitiveComponent *OtherComp,
					  int32 OtherBodyIndex) 
{
	
}
