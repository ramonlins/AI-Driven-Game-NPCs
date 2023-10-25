// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"
#include "SocketTypes.h"

Agent::Agent()
{

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
bool Agent::IsSocketCreated()
{
	return socketConnection->clientSocket != nullptr;
}

bool Agent::IsSocketConnected()
{
	if (IsSocketCreated()){
		ESocketConnectionState connectionState = socketConnection->clientSocket->GetConnectionState();
		return connectionState == ESocketConnectionState::SCS_Connected;
	}
	return false;
}
