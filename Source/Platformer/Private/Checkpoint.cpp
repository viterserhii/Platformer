#include "Checkpoint.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

