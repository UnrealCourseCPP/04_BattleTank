// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false; 

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(const FVector& HitLocation, float LaunchSpeed)
{
	// Protect Barrel Pointers
	if ( !ensure(Barrel)) { return; }	



	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = 
		UGameplayStatics::SuggestProjectileVelocity(
				this,
				OutLaunchVelocity,
				StartLocation,
				HitLocation,
				LaunchSpeed, 
				false, 0.0f, 0.0f,
				ESuggestProjVelocityTraceOption::DoNotTrace,
				FCollisionResponseParams::DefaultResponseParam,
				TArray<AActor*>(), false
				);


	// Calculate the OutLaunchVelocity

	float Time = GetWorld()->GetTimeSeconds();

	if ( bHaveAimSolution )
	{
		// Create unit AimDirection
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveWeaponTowards(AimDirection);
	}

	// If no solution found, do nothing
}

void UTankAimingComponent::MoveWeaponTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	// Work out difference between current barrel rotation and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();

	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);	
	Turret->Rotate(DeltaRotator.Yaw);
}

