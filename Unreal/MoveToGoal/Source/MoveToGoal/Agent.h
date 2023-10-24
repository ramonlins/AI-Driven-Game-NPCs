// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObservationCollector.h"

/**
 *
 */
class Agent
{
public:
	Agent();

	ObservationCollector* ObservationCollectorInstance;

	void CollectObservations(float value);
	void CollectObservations(FVector value);

	// void OnActionReceived();
	// void Heuristic();
	// void SetReward(float value);
	// void EndEpisode();

};
