// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter *ControllledCharacter = Cast<AShooterCharacter>(GetPawn());

    if (ControllledCharacter != nullptr)
    {
        return ControllledCharacter->IsDead();
    }

    return true;
}

bool AShooterAIController::CanSeePlayer() 
{
    return IsSeeingPlayer;
}

void AShooterAIController::SetCanSeePlayer(bool CanSee) 
{
    IsSeeingPlayer = CanSee;
}
