#include "SplinePlatformMover.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

ASplinePlatformMover::ASplinePlatformMover()
{
    PrimaryActorTick.bCanEverTick = true;

    Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    RootComponent = Spline;
}

void ASplinePlatformMover::BeginPlay()
{
    Super::BeginPlay();

    SplineLength = Spline->GetSplineLength();

    IslandMeshes.Empty();
    IslandOffsets.Empty();

    for (int32 i = 0; i < NumIslands; ++i)
    {
        const FString Name = FString::Printf(TEXT("Island_%d"), i);
        UStaticMeshComponent* IslandComp = NewObject<UStaticMeshComponent>(this, *Name);

        IslandComp->SetStaticMesh(IslandMesh);
        IslandComp->SetMobility(EComponentMobility::Movable);
        IslandComp->SetupAttachment(RootComponent);

        IslandComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        IslandComp->SetCollisionResponseToAllChannels(ECR_Block);

        IslandComp->RegisterComponent();

        IslandMeshes.Add(IslandComp);

        const float Alpha = static_cast<float>(i) / static_cast<float>(NumIslands);
        const float Offset = Alpha * SplineLength;
        IslandOffsets.Add(Offset);

        const FVector StartLocation =
            Spline->GetLocationAtDistanceAlongSpline(Offset, ESplineCoordinateSpace::World);

        IslandComp->SetWorldLocation(StartLocation);
        IslandComp->SetWorldScale3D(IslandScale);
    }
}

void ASplinePlatformMover::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SplineLength <= 0.0f || MoveSpeed == 0.0f || IslandMeshes.Num() == 0)
    {
        return;
    }

    BaseDistance += MoveSpeed * DeltaTime;

    for (int32 i = 0; i < IslandMeshes.Num(); ++i)
    {
        float Distance = BaseDistance + IslandOffsets[i];

        Distance = FMath::Fmod(Distance, SplineLength);
        if (Distance < 0.0f)
        {
            Distance += SplineLength;
        }

        const FVector NewLocation =
            Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

        IslandMeshes[i]->SetWorldLocation(NewLocation);
    }
}
