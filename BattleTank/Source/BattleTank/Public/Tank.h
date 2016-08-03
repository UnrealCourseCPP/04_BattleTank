// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be the last include

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
//class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "TankControls")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* TankAimingComponent = nullptr;

	//UPROPERTY(BlueprintReadOnly)
	//	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
		
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
		//UClass* ProjectileBlueprint = nullptr; // Alt is Subclassof

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed =  400.f * 100.f;	// cm/sec

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;


	// Local Barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; // TODO(spiros): Remove

	double LastFireTime = 0;
};
