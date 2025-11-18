#include "SplinePlatformMover.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"

ASplinePlatformMover::ASplinePlatformMover()
{
    PrimaryActorTick.bCanEverTick = true;

    Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    RootComponent = Spline;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    PlatformMesh->SetupAttachment(RootComponent);
    PlatformMesh->SetMobility(EComponentMobility::Movable);
}

void ASplinePlatformMover::BeginPlay()
{
    Super::BeginPlay();

    if (!Spline)
    {
        UE_LOG(LogTemp, Warning, TEXT("MovingPlatformSplineActor: Spline is null on %s"), *GetName());
        PrimaryActorTick.bCanEverTick = false;
        return;
    }

    SplineLength = Spline->GetSplineLength();

    if (SplineLength <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("MovingPlatformSplineActor: Spline length is zero on %s"), *GetName());
        PrimaryActorTick.bCanEverTick = false;
        return;
    }

    CurrentDistance = 0.0f;
}

void ASplinePlatformMover::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SplineLength <= 0.0f || MoveSpeed == 0.0f)
    {
        return;
    }

    CurrentDistance += MoveSpeed * DeltaTime;

    CurrentDistance = FMath::Fmod(CurrentDistance, SplineLength);
    if (CurrentDistance < 0.0f)
    {
        CurrentDistance += SplineLength;
    }

    const FVector NewLocation =
        Spline->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);

    PlatformMesh->SetWorldLocation(NewLocation);
}

