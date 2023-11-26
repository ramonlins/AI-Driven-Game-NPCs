// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AGoal.generated.h"

UCLASS()
class MOVETOGOAL_API AGoal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGoal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category="Goal")
	UBoxComponent* GoalBox;

	// Create StaticMesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category="Goal")
	UStaticMeshComponent* GoalMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
