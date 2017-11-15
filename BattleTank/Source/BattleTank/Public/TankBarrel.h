// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = ("Collision")) // hidecategories = ("Collision") will hide the Collison drop-down menu in details for tank->Turrent->Barrel component in Tank_BP 
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed nad +1 is max upward movement
	void Elevate(float RelativeSpeed);	

private:
	UPROPERTY(EditAnywhere, Category = Setup) // Thgis sets a drop-down menu called setup in the details tab in Tank_BP at Tank->Turrent->Barrel
		float MaxDegreesPerSecond = 10; //sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0;

	
};
