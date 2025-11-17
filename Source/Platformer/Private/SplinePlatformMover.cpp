// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePlatformMover.h"

// Sets default values
ASplinePlatformMover::ASplinePlatformMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASplinePlatformMover::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplinePlatformMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

