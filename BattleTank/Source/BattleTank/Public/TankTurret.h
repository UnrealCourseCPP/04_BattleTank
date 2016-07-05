// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"


/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision") )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 max left and +1 max right
	void Rotate(float RelativeSpeed);
	
private:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5.0f;

	/*UPROPERTY(EditAnywhere, Category = Setup)
	USceneComponent* AzimuthGimbal = nullptr;*/
	
	
};
