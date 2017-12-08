// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forword declaration for tank.h go here


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	//How close can AI tank get tp player'
	UPROPERTY(EditAnywhere, Category = "Setup") // Note* EditDefaultOnly doesn't work
	float AcceptanceRadius = 8000; // 8000 / 100 = 80 meters

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override; 


};
