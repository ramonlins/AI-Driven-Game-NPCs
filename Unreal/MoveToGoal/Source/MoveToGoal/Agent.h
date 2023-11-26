// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObservationCollector.h"
#include "SocketClient.h"

/**
 *
 */
class Agent: public ObservationCollector
{
// union observationValues{
// 	float value;
// 	FVector value;
// };

public:
	Agent();

	// Agent
	void CollectObservations(FVector value);

	// void OnActionReceived();
	// void Heuristic();
	void SetReward(float value);
	// void BeginEpisode()
	void EndEpisode(int32 value);

	// Socket
	SocketClient* socketConnection;

};
