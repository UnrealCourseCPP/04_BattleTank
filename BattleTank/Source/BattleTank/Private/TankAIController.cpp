// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
}

// Called every frame!
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* AITank = Cast<ATank>( GetPawn() );
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(AITank && PlayerTank))
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius is in cm


		// Aim at the player
		AITank->AimAt(PlayerTank->GetActorLocation());

		// Fire 
		AITank->Fire(); // TODO Limit firing rate
	}
}



