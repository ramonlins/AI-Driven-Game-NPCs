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
	// Create socket client connection
	socketConnection = new SocketClient();
	socketConnection->Connect();

	// Here you can check the socket creation and print messages
    if (Agent::IsSocketCreated()) {
        UE_LOG(LogTemp, Warning, TEXT("Client Socket was created successfully!!!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Client Socket creation failed!!!"));
    }

	// Here you can check the socket connection and print messages
    if (Agent::IsSocketConnected()) {
        UE_LOG(LogTemp, Warning, TEXT("Client Socket was connected successfully!!!"));
		// Try to see the adress and port the client is connecting
	} else {
        UE_LOG(LogTemp, Warning, TEXT("Client Socket connection failed!!!"));
    }

	// Hello server

}

// Called every frame
void AMoveAgentToGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector agentLocation = GetActorLocation();
	Agent::CollectObservations(agentLocation);

	TArray<float> AgentObservations = ObservationCollector::GetObservations();

    for (int32 i=0; i < AgentObservations.Num(); i++)
    {
        float val = AgentObservations[i];
		UE_LOG(LogTemp, Warning, TEXT("Observation Value [%i]: %f"), i, val);
    }

	ObservationCollector::ClearObservations();

}

// Called to bind functionality to input
void AMoveAgentToGoal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

