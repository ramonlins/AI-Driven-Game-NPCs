// Fill out your copyright notice in the Description page of Project Settings.


#include "AWall.h"

// Sets default values
AAWall::AAWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WallBox"));
	RootComponent = WallBox;

	WallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	WallMeshComponent->SetupAttachment(WallBox);

}

// Called when the game starts or when spawned
void AAWall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

