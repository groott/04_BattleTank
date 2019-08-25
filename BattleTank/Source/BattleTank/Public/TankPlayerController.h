// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel towards the crosshair
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirecation(FVector2D ScrenLocation, FVector& LookDirection, FVector& LookLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation, FVector& LookLocation) const;

	UPROPERTY( EditAnywhere )
	float CrossHairXLocation = 0.5f;

	UPROPERTY( EditAnywhere )
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;
};
