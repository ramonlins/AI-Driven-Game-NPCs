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

}

// Called every frame
void AMoveAgentToGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector agentLocation = GetActorLocation();
	Agent::CollectObservations(agentLocation);

	TArray<float> AgentObservations = Agent::GetObservations();

	// Create the buffer
    TArray<uint8> SendBuffer;
	FMemoryWriter Writer(SendBuffer);

    for (int32 i=0; i < AgentObservations.Num(); i++)
    {
        float val = AgentObservations[i];
		Writer << val;
		UE_LOG(LogTemp, Warning, TEXT("Observation Value [%i]: %f"), i, val);
    }

	// Send data to server
	if (socketConnection->IsSocketConnected()){
        // Track how many bytes were actually sent over the socket.
        int32 BytesSent = 0;
        // Retrieve pointer, number of bytes and send over socket
        socketConnection->clientSocket->Send(SendBuffer.GetData(), SendBuffer.Num(), BytesSent);
    }

	Agent::ClearObservations();

}

// Called to bind functionality to input
void AMoveAgentToGoal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

