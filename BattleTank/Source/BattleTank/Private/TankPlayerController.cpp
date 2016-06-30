// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller BeginPlay()"));

	ATank* ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankPC can't find possessed Tank!"));
	}
}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("Player Controller Tick()!"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return;  }

	FVector HitLocation;	// Out parameter

	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString() );

		
		// TODO Tell controlled tank to aim at this point
		
	}

}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	bool HasHit = false;

	// Get WorldLocation of Sight 
		// Get the ScreenSpace position of the image that represents Sight
		// Deproject it to world position
	// Set that as LineStart
	// Get Direction the camera is facing at(forward vector of camera(?))
	// Create LineEnd using the direction ,LineStart and a range
	// Create needed structures for Linetracing (FHitResult, FQueryParams, etc)
	// LineTraceSingleByChannel(?)
	// If we hit something 
		// Get the Location in WorldSpace
		// Set OUT HitLocation to the above location and return true
	// Otherwise return false

	HitLocation = FVector(1.0f);

	//return HasHit;
	return true;
}




