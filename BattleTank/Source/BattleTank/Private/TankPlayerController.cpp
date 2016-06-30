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

	// Get world location if linetrace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}




