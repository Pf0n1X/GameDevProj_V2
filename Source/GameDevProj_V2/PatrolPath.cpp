// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPath.h"
#include "Containers/Array.h"
#include "Math/Vector.h"

// Sets default values
APatrolPath::APatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FVector> APatrolPath::GetPatrolPathPoints() 
{
	TArray<FVector> Result;

	for (FVector Item: PatrolPathPoints)
	{
		Result.Add(GetTransform().GetLocation() + Item);
	}

	return Result;
}

