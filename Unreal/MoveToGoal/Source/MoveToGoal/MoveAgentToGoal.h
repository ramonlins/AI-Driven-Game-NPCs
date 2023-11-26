// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Agent.h"
#include "AWall.h"
#include "AGoal.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "MoveAgentToGoal.generated.h"

UCLASS()
class MOVETOGOAL_API AMoveAgentToGoal : public APawn, public Agent
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMoveAgentToGoal();

	FVector agentLocation;
	FVector targetLocation;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Move by inference
	void MoveAgent(FVector direction, float deltaTime);

	// Move by keyboard
	void MoveVertical(float value);
	void MoveHorizontal(float value);

	// Called when detect overlap between agent and other actors
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Flags for collision
	bool bHitWall;
	bool bHitGoal;

	// Flag to select control of agent
	bool bIsHeuristic;

	// Set the trigger box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
    UBoxComponent* TriggerBox;

	// Set to BP a box component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
	UBoxComponent* CubeBox;

	// Set to BP a cube mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
	UStaticMeshComponent* CubeMeshComponent;

	// Set to BP the camera component
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;


	// Set to BP a cube mesh component
	UPROPERTY(EditAnywhere)
	float agentSpeed = 5.f;

	float zValue = 33.f;

	int counter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float verticalInputValue;
	float horizontalInputValue;

	AGoal* goalActor;
};
