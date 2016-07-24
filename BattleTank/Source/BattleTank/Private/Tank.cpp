// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// No need to protect pointers as added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

}

// Called when the game starts or when spawned
//void ATank::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
//{
//	Super::SetupPlayerInputComponent(InputComponent);
//
//}

void ATank::AimAt(FVector HitLocation)
{
	
	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

//void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//	if (TankAimingComponent)
//	{
//		TankAimingComponent->SetBarrelReference(BarrelToSet);
//	}
//	Barrel = BarrelToSet;
//}

//void ATank::SetTurretReference(UTankTurret* TurretToSet)
//{
//	if (TankAimingComponent)
//	{
//		TankAimingComponent->SetTurretReference(TurretToSet);
//	}
//}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{

		// Spawn a projectile at the socket location
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
								ProjectileBlueprint,
								Barrel->GetSocketLocation(FName("Projectile")),
								Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

