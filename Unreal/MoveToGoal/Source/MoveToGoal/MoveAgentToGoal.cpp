// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAgentToGoal.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMoveAgentToGoal::AMoveAgentToGoal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CubeBox"));
	RootComponent = CubeBox;

	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMeshComponent->SetupAttachment(CubeBox);

	// Set initial position to zero relative to process
	agentLocation = FVector{0.f, 0.f, 32.f};
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
	// Collect agent location and target location
	//agentLocation = GetActorLocation();
	Agent::CollectObservations(agentLocation);

	// Get all locations
	TArray<float> allObservations = Agent::GetObservations();

	// Send to server
	socketConnection->Send(allObservations);

	// Receive action
	FVector newObservations = socketConnection->Receive();

	// Get world delta time (Current drawn frame  - previous drawn frame)
	static double deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	// Update new location
	agentLocation.X += newObservations.X * deltaTime * agentSpeed;
	agentLocation.Y += newObservations.Y * deltaTime * agentSpeed;

	// Set agent to new location based on delta time
	SetActorLocation(agentLocation);

	Agent::ClearObservations();

}

// Called to bind functionality to input
void AMoveAgentToGoal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
