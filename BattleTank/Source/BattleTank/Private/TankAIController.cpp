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


