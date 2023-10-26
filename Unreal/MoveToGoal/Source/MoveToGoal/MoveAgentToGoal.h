// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Agent.h"
#include "Components/BoxComponent.h"
#include "MoveAgentToGoal.generated.h"

UCLASS()
class MOVETOGOAL_API AMoveAgentToGoal : public APawn, public Agent
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMoveAgentToGoal();
	FVector agentLocation;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Set to BP a box component
	UPROPERTY(EditAnywhere)
	UBoxComponent* CubeBox;

	// Set to BP a cube mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CubeMeshComponent;

	// Set to BP a cube mesh component
	UPROPERTY(EditAnywhere)
	float agentSpeed = 1.f;
};
