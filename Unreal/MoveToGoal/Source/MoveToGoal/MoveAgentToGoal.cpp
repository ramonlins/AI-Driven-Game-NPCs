// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAgentToGoal.h"

// Sets default values
AMoveAgentToGoal::AMoveAgentToGoal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CubeBox"));
	RootComponent = CubeBox;

	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMeshComponent->SetupAttachment(CubeBox);

}

// Called when the game starts or when spawned
void AMoveAgentToGoal::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMoveAgentToGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector agentLocation = GetActorLocation();
	CollectObservations(agentLocation);

	TArray<float> AgentObservations = ObservationCollectorInstance->GetObservations();

    for (int32 i=0; i < AgentObservations.Num(); i++)
    {
        float val = AgentObservations[i];
		UE_LOG(LogTemp, Warning, TEXT("Observation Value: %f"), val);
    }

	ObservationCollectorInstance->ClearObservations();

}

// Called to bind functionality to input
void AMoveAgentToGoal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

