// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller BeginPlay()"));

	UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController can't find AimingCompoent at BeginPlay()"));
	}

}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { return;  }

	
	FVector HitLocation;	// Out parameter

	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{	
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		
		// Tell controlled tank to aim at this point	
		GetControlledTank()->AimAt(HitLocation);
	}

}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("Sight Screen Location: %s"), *ScreenLocation.ToString());

	// De-Project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{	
		// Line trace along that look direction and see what we hit (up to max range)
		if ( GetLookVectorHitLocation(HitLocation, LookDirection) )		
		{
			return true;
		}
	}
		
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // Camera World Location, we don't need it but it's an OUT param

	return DeprojectScreenPositionToWorld(
			ScreenLocation.X, 
			ScreenLocation.Y, 
			CameraWorldLocation, 
			LookDirection);	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, const FVector& LookDirection) const
{
	FHitResult HitResult;

	FCollisionQueryParams Params(NAME_None, false, GetControlledTank());
	//FCollisionResponseParams ResponseParams(ECollisionResponse::ECR_Block);

	//FVector Start = GetControlledTank()->GetActorLocation();
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params) )
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}




