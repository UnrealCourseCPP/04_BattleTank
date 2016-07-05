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
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this really Tick??

	// ...
}


// Barrel Reference Setter
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

// Turret reference Setter
void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(const FVector& HitLocation, float LaunchSpeed)
{
	// Protect Barrel & Turret Pointers
	if ( ! Barrel || ! Turret) { return; }	



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
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution found"), Time);
		
		
		// Create unit AimDirection
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveWeaponTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
	}

	// If no solution found, do nothing
}

void UTankAimingComponent::MoveWeaponTowards(FVector AimDirection)
{
	// Work out difference between current barrel rotation and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();

	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %f"), DeltaRotator.Pitch);

	Barrel->Elevate(DeltaRotator.Pitch);	
	Turret->Rotate(DeltaRotator.Yaw);
}

