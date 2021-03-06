// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include


class ATank;
class UTankAimingComponent;
/**
 * Responsible for helping the player aim 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);

private:
	virtual void BeginPlay() override;

	virtual void Tick( float DeltaTime ) override;


	// Start the tank moving the barrel so that a shot
	// would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT paramater, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector& HitLocation, const FVector& LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 10000.f * 100.f; // 10km

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333f;
	
	
	
};
