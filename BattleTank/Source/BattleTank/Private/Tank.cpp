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

	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank %s C++ CTOR running!"), *GetName());
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank %s C++ BeginPlay() running!"), *GetName());  

	Super::BeginPlay(); // Needed for BP BeginPlay to run!
}

// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
//{
//	Super::SetupPlayerInputComponent(InputComponent);
//
//}

void ATank::AimAt(FVector HitLocation)
{	
	if (!ensure(TankAimingComponent)) { return; }
	
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);	
}


void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
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

