// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

Agent::Agent()
{
	// Create socket client connection
	SocketConnection = new SocketClient();
}

void Agent::CollectObservations(float location)
{
	AddObservations(location);

}

void Agent::CollectObservations(FVector location)
{
	AddObservations(location);

}
// Check if socket was created successfully
bool Agent::IsSocketConnected()
{
	return SocketConnection->ClientSocket != nullptr;
}
