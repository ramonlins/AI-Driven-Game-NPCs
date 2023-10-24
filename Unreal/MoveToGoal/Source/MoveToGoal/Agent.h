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
public:
	Agent();

	void CollectObservations(float value);
	void CollectObservations(FVector value);

	// void OnActionReceived();
	// void Heuristic();
	// void SetReward();
	// void BeginEpisode()
	// void EndEpisode();

	// Declare socket client
	SocketClient* SocketConnection;

	bool IsSocketConnected();
};
