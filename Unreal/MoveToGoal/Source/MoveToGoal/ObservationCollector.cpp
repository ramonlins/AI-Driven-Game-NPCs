// Fill out your copyright notice in the Description page of Project Settings.


#include "ObservationCollector.h"

ObservationCollector::ObservationCollector()
{

}

void ObservationCollector::AddObservation(float value)
{
    Observations.Add(value);
}

void ObservationCollector::AddObservation(FVector value)
{
    Observations.Add(value.X);
    Observations.Add(value.Y);
    Observations.Add(value.Z);

}

TArray<float> ObservationCollector::GetObservations() const
{
    return Observations;
}

void ObservationCollector::ClearObservations()
{
    Observations.Empty();
}
