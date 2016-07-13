// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply
 * forces to the tank.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category="Input")
	void SetThrottle(float Throttle);


private:
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		float TrackMaxDrivingForce = 400000.f; // Newtons assuming 40 ton tank and 1g acceleration
};
