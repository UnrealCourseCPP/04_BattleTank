// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Barrel Reference Setter
void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
	
}


void UTankAimingComponent::AimAt(const FVector& HitLocation) const
{
	// Get parent Tank's name
	//FString OurTankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming at: %s"), *OurTankName, *HitLocation.ToString());

	// See if we have a valid barrel and print it's location if we do
	if (Barrel)
	{
		UE_LOG(LogTemp, Warning, 
			TEXT("TankAimingComponent on Tank %s got a Barrel at: %s, aiming at %s"),
			*GetOwner()->GetName(), 
			*Barrel->GetComponentLocation().ToString(),
			*HitLocation.ToString());
	}
}

