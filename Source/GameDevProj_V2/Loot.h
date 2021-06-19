// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Loot.generated.h"

UCLASS()
class GAMEDEVPROJ_V2_API ALoot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *OverlappedComp,
						AActor *OtherActor,
						UPrimitiveComponent *OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult &SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
					  class AActor *OtherActor,
					  class UPrimitiveComponent *OtherComp,
					  int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Mesh;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent *TriggerCapsule;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystem *PickupParticles;

	UPROPERTY(EditAnywhere)
	USoundBase *PickupSound;
};
