// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Has side-effect, is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}

}

// Get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find corsshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// De-project screen position of the crosshair to ta world direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	// Line-trace along LookDirection and see what is hit(up to a max range)

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if ( GetWorld()->LineTraceSingleByChannel // Doesn't like LineTraceSingleByLocation
	(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
	 ) 
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);

}