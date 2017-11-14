// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine.h"




// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //will look for socket named Projectile
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,				//Uboject 8 WorldContextObject
		OutLaunchVelocity,  //FVector & TossVelocity
		StartLocation,		// FVector StartLocation
		HitLocation,		// FVector EndLocation
		LaunchSpeed,		// float TossSpeed
		ESuggestProjVelocityTraceOption::DoNotTrace // ESuggestProjVelocityTraceOption
	);

	if( bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //GetSafeNormal gets a copy of the vector if the length is not too small
		MoveBarrelTowards(AimDirection);
	}
	// If no solution, do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	// Workout difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	//Move the barrel the right amount this frame

	// Give a max elevation speed and frame time
}