#include "MeshMoverAlongSplineComponent.h"

UMeshMoverAlongSplineComponent::UMeshMoverAlongSplineComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMeshMoverAlongSplineComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentProgress = StartAtProgress * SplineComponent->GetSplineLength();
    TimeSinceStarted = CurrentProgress / MovementSpeed;
}

void UMeshMoverAlongSplineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (SplineComponent)
    {
        TimeSinceStarted += DeltaTime;
        CurrentProgress = FMath::Fmod(TimeSinceStarted * MovementSpeed, SplineComponent->GetSplineLength());

        FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentProgress, ESplineCoordinateSpace::World);
        SetWorldLocation(NewLocation);
    }
}