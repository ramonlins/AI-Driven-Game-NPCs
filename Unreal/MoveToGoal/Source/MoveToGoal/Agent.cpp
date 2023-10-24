// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

// Sets default values
AAgent::AAgent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObservationCollectorInstance = new ObservationCollector();

	// Create agent mesh component and set it as root
	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMeshComponent;
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();

}

void AAgent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	CollectLocationObservation();

	TArray<float> AgentObservations = ObservationCollectorInstance->GetObservations();

    for (int32 i=0; i < AgentObservations.Num(); i++)
    {
        float val = AgentObservations[i];
		UE_LOG(LogTemp, Warning, TEXT("Observation Value: %f"), val);
    }

	ObservationCollectorInstance->ClearObservations();

}

// Called to bind functionality to input
void AAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAgent::CollectLocationObservation()
{
	FVector Location = GetActorLocation();
	ObservationCollectorInstance->AddObservation(Location);

}

