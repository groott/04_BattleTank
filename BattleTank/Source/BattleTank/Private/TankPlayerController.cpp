// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank is not possesed by TankPlayerController"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController is possesing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // OUT Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScrenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	FVector LookLocation;
	if (GetLookDirecation(ScrenLocation, LookDirection, LookLocation))
	{
		// Line Tracing
		GetLookVectorHitLocation(LookDirection, HitLocation, LookLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirecation(FVector2D ScrenLocation, FVector& LookDirection, FVector& LookLocation) const
{
	return DeprojectScreenPositionToWorld(ScrenLocation.X, ScrenLocation.Y, LookLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation, FVector& LookLocation) const
{
	FHitResult HitResult;

	auto EndLocation = LookLocation + (LookDirection * LineTraceRange);

	// DrawDebugLine(GetWorld(), LookLocation,	EndLocation, FColor(255, 0, 0),	false, -1, 1, 5);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, LookLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}