// Fill out your copyright notice in the Description page of Project Settings.


#include "ObservationCollector.h"

ObservationCollector::ObservationCollector()
{

}
// Add one float value
void ObservationCollector::AddObservations(float value)
{
    observations.Add(value);
}

// Add vector values (x, y, z)
void ObservationCollector::AddObservations(FVector value)
{
    observations.Add(value.X);
    observations.Add(value.Y);
    observations.Add(value.Z);

}

void ObservationCollector::AddObservations(int32 value)
{
    observations.Add(value);
}

// Get the added observations
TArray<float> ObservationCollector::GetObservations() const
{
    return observations;
}

// Clear the added observations
void ObservationCollector::ClearObservations()
{
    observations.Empty();
}

