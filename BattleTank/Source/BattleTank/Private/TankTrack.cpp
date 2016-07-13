// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%f: %s Throttle: %f"), GetWorld()->GetTimeSeconds(), *GetName(), Throttle);

	// TODO(spiros): Clamp actual throttle value so player can't overdrive

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


