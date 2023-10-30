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
	FVector targetLocation;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerBox;

	bool bHitWall;
	bool bHitGoal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Set to BP a box component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
	UBoxComponent* CubeBox;

	// Set to BP a cube mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agent")
	UStaticMeshComponent* CubeMeshComponent;

	// Set to BP a cube mesh component
	UPROPERTY(EditAnywhere)
	float agentSpeed = 5.f;
};
