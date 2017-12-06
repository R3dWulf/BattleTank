// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Engine.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // Should this really tick???

	// ...
}

void  UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //will look for socket named Projectile
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,				//Uboject 8 WorldContextObject
		OutLaunchVelocity,  //FVector & TossVelocity
		StartLocation,		// FVector StartLocation
		HitLocation,		// FVector EndLocation
		LaunchSpeed,		// Float TossSpeed
		false,				// Boolean Favor High Arc
		0,					// Float Collision Radius
		0					// Float OverrideGravityZ
		,ESuggestProjVelocityTraceOption::DoNotTrace //Enum Trace Option
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
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Workout difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;


	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}