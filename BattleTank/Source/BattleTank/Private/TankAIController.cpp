// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	// Log ControlledTank
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController doesn't currently possess a Tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing: %s"), *ControlledTank->GetName());
	}

	// Log PlayerTank
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController ---> Could not get Player Tank!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController got Player Tank: %s"), *PlayerTank->GetName());
	}
}

// Called every frame!
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* AITank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (AITank && PlayerTank)
	{
		// TODO Move towards the player

		// Aim at the player
		AITank->AimAt(PlayerTank->GetActorLocation());

		// TODO Fire when ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{	
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr;  }

	return Cast<ATank>(PlayerPawn);
}


