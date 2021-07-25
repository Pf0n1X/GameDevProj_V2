// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVPROJ_V2_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	bool IsDead() const;

	UFUNCTION(BlueprintCallable)
	bool CanSeePlayer();

	UFUNCTION(BlueprintCallable)
	void SetCanSeePlayer(bool CanSee);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere);
	class UBehaviorTree* AIBehavior;

	UPROPERTY(EditAnywhere)
	bool IsSeeingPlayer = false;
};
