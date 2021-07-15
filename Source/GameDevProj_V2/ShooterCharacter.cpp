// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"
#include "Gun.h"
#include "PatrolPath.h"
#include "Components/CapsuleComponent.h"
#include "GameDevProj_V2GameModeBase.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	for (TSubclassOf<AGun> GunClass : GunClasses)
	{
		AGun *Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
		Gun->SetOwner(this);
		Gun->SetHidden(true);
		Guns.Add(Gun);
	}

	if (Guns.GetData() != nullptr)
	{
		Guns.GetData()[0]->SetHidden(false);
	}

	FPSCamera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("FPS_Camera")));
	TPSCamera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("Camera")));
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("NextWeapon"), EInputEvent::IE_Pressed, this, &AShooterCharacter::NextWeapon);
	PlayerInputComponent->BindAction(TEXT("PreviousWeapon"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PreviousWeapon);
	PlayerInputComponent->BindAction(TEXT("TogglePerspective"), EInputEvent::IE_Pressed, this, &AShooterCharacter::TogglePerspective);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead())
	{
		AGameDevProj_V2GameModeBase *GameMode = GetWorld()->GetAuthGameMode<AGameDevProj_V2GameModeBase>();

		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::NextWeapon()
{
	// Add 1 to the active index
	ActiveIndex += 1;

	// Make sure it doesn't go above the guns array size,
	ActiveIndex %= Guns.Num();

	HideAndShowWeapons();
}

void AShooterCharacter::PreviousWeapon()
{
	// Add 1 to the active index
	ActiveIndex += (Guns.Num() - 1);

	// Make sure it doesn't go above the guns array size,
	ActiveIndex %= Guns.Num();

	HideAndShowWeapons();
}

void AShooterCharacter::HideAndShowWeapons() 
{
	// Hide all the weapons
	for (AGun *Gun : Guns)
	{
		Gun->SetActorHiddenInGame(true);
	}

	// Show the selected one.
	Guns[ActiveIndex]->SetActorHiddenInGame(false);
}

void AShooterCharacter::TogglePerspective() 
{
	if (IsFPSCameraActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("T1"));
		// FPSCamera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("FPS_Camera")));

		if (FPSCamera != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("T3"));
			FPSCamera->SetActive(false);
			TPSCamera->SetActive(true);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("T2"));
		// UCameraComponent *FPSCamera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("FPS_Camera")));

		if (FPSCamera != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("T3"));
			FPSCamera->SetActive(true);
			TPSCamera->SetActive(false);
		}
	}

	IsFPSCameraActive = !IsFPSCameraActive;
}

void AShooterCharacter::Shoot()
{
	if (IsAllowedToShoot)
	{
		Guns.GetData()[ActiveIndex]->PullTrigger();
	}
}

TArray<FVector> AShooterCharacter::GetPatrolPath() 
{
	return PatrolPathPoints->GetPatrolPathPoints();
}

int32 AShooterCharacter::GetAmmo() const
{
	return Guns[ActiveIndex]->GetAmmo();
}

bool AShooterCharacter::IsAllowedToPickup() const
{
	return IsAllowedToPickupLoot;
}

void AShooterCharacter::FillActiveGunAmmo() 
{
	Guns[ActiveIndex]->FillAmmo();
}

void AShooterCharacter::AllowShooting(bool IsAllowed) 
{
	IsAllowedToShoot = IsAllowed;
}