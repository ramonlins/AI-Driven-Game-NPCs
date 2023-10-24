// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

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
