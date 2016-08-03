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
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Turning with throw = %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super() as we are replacing the functionality
	
	//UE_LOG(LogTemp, Warning, TEXT("In RequestDirectMove"));

	// Get tank's forward vector (also normalised)
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	// Get normalized direction we want to move to
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("MoveVelocity = %s"), *AIForwardIntention.ToString() );

	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	// Use result of dot product of AIForwardIntention and TankForward as Throw
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	UE_LOG(LogTemp, Warning, TEXT("Cross.Z = %f"), RightThrow);
	IntendTurnRight(RightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("In UTankMovementComponent::RequestDirectMove(), from tank: %s , MoveVelocity: %s"), *GetOwner()->GetName(), *AIForwardIntention.ToString() );
}


