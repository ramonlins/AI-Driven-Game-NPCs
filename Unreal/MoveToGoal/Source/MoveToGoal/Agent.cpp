// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

Agent::Agent()
{
    ObservationCollectorInstance = new ObservationCollector();
}

void Agent::CollectObservations(float location)
{
	ObservationCollectorInstance->AddObservations(location);

}

void Agent::CollectObservations(FVector location)
{
	ObservationCollectorInstance->AddObservations(location);

}
