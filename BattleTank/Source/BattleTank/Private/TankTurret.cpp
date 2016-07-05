// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the turret the right amount this frame
	// given a clamped RelativeSpeed (-1 max left, +1 max right)
	float RotationChange = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();

	float NewRotation = RelativeRotation.Yaw + RotationChange;
	
	// No clamp on rotation here??

	SetRelativeRotation(FRotator(0, NewRotation, 0));
	//AddRelativeRotation(FRotator(0, RotationChange, 0));

}


