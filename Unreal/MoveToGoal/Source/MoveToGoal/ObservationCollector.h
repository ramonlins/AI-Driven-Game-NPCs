// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class ObservationCollector
{
public:
	ObservationCollector();

	// Add observations
	void AddObservations(float value);
	void AddObservations(FVector value);
	void AddObservations(int32 value);

	// Get observations
	TArray<float> GetObservations() const;

	// Clear observations
	void ClearObservations();

	// Array of observations
	TArray<float> observations;
};
