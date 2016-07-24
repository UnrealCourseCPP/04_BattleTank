// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus :uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;

// Component that aids in Aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Setters
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

	
	// Called externally
	void AimAt(const FVector& HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveWeaponTowards(FVector AimDirection);

	
};
