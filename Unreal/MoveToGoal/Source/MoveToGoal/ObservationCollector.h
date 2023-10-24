// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"

/**
 *
 */
class MOVETOGOAL_API ObservationCollector
{
public:
	ObservationCollector();

	void AddObservation(float value);
	void AddObservation(FVector value);

	TArray<float> GetObservations() const;
	void ClearObservations();

	TArray<float> Observations;

};
