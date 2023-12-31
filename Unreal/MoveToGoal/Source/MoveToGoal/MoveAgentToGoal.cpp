// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAgentToGoal.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMoveAgentToGoal::AMoveAgentToGoal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Define box
	CubeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Cube Box"));
	RootComponent = CubeBox;

	// Define mesh
	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	CubeMeshComponent->SetupAttachment(CubeBox);

	// Create and setup the trigger box
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(CubeMeshComponent);

	// Set trigger default profile (ignore physics)
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	// Call overlap behavior when the agent (this) start to overlap with another component
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMoveAgentToGoal::OnOverlapBegin);

	// Define Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Set initial position to zero relative to process
	agentLocation = FVector{0.f, 0.f, zValue};
	targetLocation = FVector{101.f, -95.f, 15.f};

	// Set agent to learn or be possed
	bIsHeuristic = true;

	counter = 0;
}

// Called when the game starts or when spawned
void AMoveAgentToGoal::BeginPlay()
{
	Super::BeginPlay();

	// Create socket client connection
	socketConnection = new SocketClient();
	socketConnection->Connect();

	// Find goal actor
	goalActor = Cast<AGoal>(UGameplayStatics::GetActorOfClass(GetWorld(), AGoal::StaticClass()));
}

// Called every frame
void AMoveAgentToGoal::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	counter += 1;

	// Collect agent location and target location
	Agent::CollectObservations(agentLocation);
	Agent::CollectObservations(targetLocation);

	if (bHitWall){
		Agent::SetReward(-10.f);
		Agent::EndEpisode(1);
	}else if (bHitGoal){
		Agent::SetReward(100.f);
		Agent::EndEpisode(1);
	}else if (counter >= 1000){
		Agent::SetReward(-0.1f);
		Agent::EndEpisode(1);

	}else{
		Agent::SetReward(-0.01f);
		Agent::EndEpisode(0);
	}

	// Get all observations
	TArray<float> allObservations = Agent::GetObservations();

	// Send to server
	socketConnection->Send(allObservations);

	// Player or agent controll
	if (bIsHeuristic){
		// Received action
		FVector movementDirection = socketConnection->Receive();

		MoveAgent(movementDirection, deltaTime);
	}else{
		FVector movementDirection = FVector(verticalInputValue, horizontalInputValue, zValue);

		MoveAgent(movementDirection, deltaTime);

	}

	if (bHitWall || bHitGoal || counter >= 1000){
		agentLocation = FVector{0.f, 0.f, zValue};

		if (goalActor){
			float mirrorX = (rand() % 2) * 2 - 1;
			float mirrorY = (rand() % 2) * 2 - 1;

			float randomX = FMath::FRandRange(70.0f, 160.0f) * mirrorX;
			float randomY = FMath::FRandRange(0.0f, 160.0f) * mirrorY;

			FVector newGoalLocation = FVector{randomX, randomY, 15.f};
			goalActor->SetActorLocation(newGoalLocation);
			targetLocation = newGoalLocation;
		}

		if (bHitWall){
			bHitWall = false;
		}else{
			bHitGoal = false;
		}
		counter = 0;
	}else{
		SetActorLocation(agentLocation, true);
	}

	Agent::ClearObservations();

}

// Called to bind functionality to input
void AMoveAgentToGoal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &AMoveAgentToGoal::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &AMoveAgentToGoal::MoveHorizontal);

}

void AMoveAgentToGoal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor){
		if (OtherActor->IsA(AAWall::StaticClass())){
			bHitWall = true;
			// TODO: Change material, end episode, etc.
		}

		if (OtherActor->IsA(AGoal::StaticClass())){
			bHitGoal = true;
			UE_LOG(LogTemp, Warning, TEXT("Hit the wall Value: %?"), bHitGoal);
		    // TODO: Change material, end episode, etc.
		}

    }
}

// Move agent based on new observations
void AMoveAgentToGoal::MoveAgent(FVector newObservations, float deltaTime){

	// Update new location
	agentLocation.X += newObservations.X * deltaTime * agentSpeed;
	agentLocation.Y += newObservations.Y * deltaTime * agentSpeed;

}

// Move Agent in vertical
void AMoveAgentToGoal::MoveVertical(float value)
{
	verticalInputValue = value;

}
// Move agent in horizontal
void AMoveAgentToGoal::MoveHorizontal(float value)
{
	horizontalInputValue = value;

}
