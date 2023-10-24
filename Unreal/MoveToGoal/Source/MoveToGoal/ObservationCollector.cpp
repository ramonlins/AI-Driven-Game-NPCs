// Fill out your copyright notice in the Description page of Project Settings.


#include "ObservationCollector.h"

ObservationCollector::ObservationCollector()
{

}

void ObservationCollector::AddObservations(float value)
{
    observations.Add(value);
}

void ObservationCollector::AddObservations(FVector value)
{
    observations.Add(value.X);
    observations.Add(value.Y);
    observations.Add(value.Z);

}

TArray<float> ObservationCollector::GetObservations() const
{
    return observations;
}

void ObservationCollector::ClearObservations()
{
    observations.Empty();
}

