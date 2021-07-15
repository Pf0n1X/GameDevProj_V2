// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameInstance.h"
#include "ShooterCharacter.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);

    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromViewport();

    // Disable Player Shooting
    AShooterCharacter *PlayerCharacter = Cast<AShooterCharacter>(GetPawn());

    if (PlayerCharacter != nullptr)
    {
        PlayerCharacter->AllowShooting(false);
    }

    UShooterGameInstance *ShooterGameInstance = Cast<UShooterGameInstance>(GetGameInstance());

    if (ShooterGameInstance == nullptr)
    {
        return;
    }

    if (bIsWinner)
    {
        ShooterGameInstance->CurLevel++;

        if (ShooterGameInstance->CurLevel == LevelsAmount)
        {
            ShooterGameInstance->CurLevel = 0;

            // Show Win Screen
            UUserWidget *WinScreen = CreateWidget(this, WinScreenClass);

            if (WinScreen != nullptr)
            {
                WinScreen->AddToViewport();
            }
        }
        else
        {
            // Show Next Level Screen
            UUserWidget *NextLevelScreen = CreateWidget(this, NextLevelScreenClass);

            if (NextLevelScreen != nullptr)
            {
                NextLevelScreen->AddToViewport();
            }
        }
    }
    else
    {
        ShooterGameInstance->CurLevel = 0;
        UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);

        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::RestartLevel()
{
    Super::RestartLevel();

    UShooterGameInstance *ShooterGameInstance = Cast<UShooterGameInstance>(GetGameInstance());

    if (ShooterGameInstance != nullptr)
    {
        UGameplayStatics::OpenLevel(GetWorld(), LevelNames[ShooterGameInstance->CurLevel]);

        //  Enable Player Shooting
        AShooterCharacter *PlayerCharacter = Cast<AShooterCharacter>(GetPawn());

        if (PlayerCharacter != nullptr)
        {
            PlayerCharacter->AllowShooting(true);
        }
    }
}