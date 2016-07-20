// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO(spiros): Prevent double speed due to dual control
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super() as we are replacing the functionality

	// Get normalized direction we want to move to
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	// Get tank's forward vector (also normalised)
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// Use result of dot product of AIForwardIntention and TankForward as Throw
	IntendMoveForward(FVector::DotProduct(AIForwardIntention, TankForward));

	//UE_LOG(LogTemp, Warning, TEXT("In UTankMovementComponent::RequestDirectMove(), from tank: %s , MoveVelocity: %s"), *GetOwner()->GetName(), *AIForwardIntention.ToString() );
}


