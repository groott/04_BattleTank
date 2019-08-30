// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * 
 */
UCLASS( meta = ( BlueprintSpawnableComponent ) )
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Setting throttle to tracks
	UFUNCTION( BlueprintCallable, Category = Input )
	void SetThrottle(float Throttle);
	
	// Max force per track, in Newtons
	UPROPERTY( EditDefaultsOnly )
	float TrackMaxDrivingForce = 400000; // Assume 40 tone tank, and 1 g acceleration
};
