// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class APatrolPath;
class UCameraComponent;

UCLASS()
class GAMEDEVPROJ_V2_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

	TArray<FVector> GetPatrolPath();

	UFUNCTION(BlueprintPure)
	int32 GetAmmo() const;

	UFUNCTION(BlueprintPure)
	bool IsAllowedToPickup() const;

	UFUNCTION()
	void FillActiveGunAmmo();

	UFUNCTION()
	void AllowShooting(bool IsAllowed);

	UFUNCTION(BlueprintCallable)
	void GetKIlled(class AController *EventInstigator, AActor *DamageCauser);

	UFUNCTION(BLueprintCallable)
	AGun* GetActiveGun() const;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void NextWeapon();
	void PreviousWeapon();
	void HideAndShowWeapons();
	void TogglePerspective();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent *FPSCamera;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent *TPSCamera;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AGun>> GunClasses;

	// UPROPERTY()
	// AGun* Gun;

	UPROPERTY(EditAnywhere)
	TArray<AGun*> Guns;
	
	int ActiveIndex;

	UPROPERTY(EditAnywhere)
	bool IsAllowedToPickupLoot = true;

	bool IsFPSCameraActive = false;

	UPROPERTY(EditInstanceOnly, Meta = (MakeEditWidget = true))
	APatrolPath* PatrolPathPoints;


	UPROPERTY(EditAnywhere)
	bool IsAllowedToShoot = true;
};
