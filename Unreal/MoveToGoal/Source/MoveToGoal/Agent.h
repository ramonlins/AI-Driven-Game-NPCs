// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ObservationCollector.h"
#include "Agent.generated.h"

UCLASS()
class MOVETOGOAL_API AAgent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAgent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Get location of character
	ObservationCollector* ObservationCollectorInstance;
	void CollectLocationObservation();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMeshComponent;
};
