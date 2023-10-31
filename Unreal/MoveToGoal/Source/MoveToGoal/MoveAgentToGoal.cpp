// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAgentToGoal.h"
#include "AWall.h"
#include "AGoal.h"
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
	CubeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Cube Box"));
	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	CubeMeshComponent->SetupAttachment(TriggerBox);

	// Set initial position to zero relative to process
	agentLocation = FVector{0.f, 0.f, 33.f};
	targetLocation = FVector{191.f, -15.f, 0.f};

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
void AMoveAgentToGoal::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	// Collect agent location and target location
	//agentLocation = GetActorLocation();
	Agent::CollectObservations(agentLocation);
	Agent::CollectObservations(targetLocation);

	if (bHitWall){
		Agent::SetReward(-1.f);
		Agent::EndEpisode(1);
	}else if (bHitGoal){
		Agent::SetReward(10.f);
		Agent::EndEpisode(1);
	}else{
		Agent::SetReward(-0.1f);
		Agent::EndEpisode(0);
	}

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
	if (bHitWall){
		bHitWall = false; // Reset the flag
		agentLocation = FVector{0.f, 0.f, 33.f};
	}else{
		SetActorLocation(agentLocation, true);
	}

	Agent::ClearObservations();

}

// Called to bind functionality to input
void AMoveAgentToGoal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMoveAgentToGoal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor){
		if (OtherActor->IsA(AAWall::StaticClass())){
			bHitWall = true;
			// Handle wall logic
            // Agent::SetReward(-1.f);
            // Change material, end episode, etc.
		}else if (OtherActor->IsA(AGoal::StaticClass())){
			bHitGoal = true;
			// Handle wall logic
            // Agent::SetReward(-1.f);
            // Change material, end episode, etc.
		}

        // // Check for Wall component
        // UBoxComponent* WallBox = Cast<UBoxComponent>(OtherActor->GetComponentByClass(UBoxComponent::StaticClass()));
        // if (WallBox)
        // {
        //  	bHitWall = true;
		// 		Handle wall logic
        //     // Agent::SetReward(-1.f);
        //     // Change material, end episode, etc.
        // }
    }
}
