// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AWall.generated.h"

UCLASS()
class MOVETOGOAL_API AAWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Set to BP a cube mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	UBoxComponent* WallBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	UStaticMeshComponent* WallMeshComponent;
};
