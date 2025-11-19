#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePlatformMover.generated.h"

class USplineComponent;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS()
class PLATFORMER_API ASplinePlatformMover : public AActor
{
    GENERATED_BODY()

public:
    ASplinePlatformMover();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline")
    USplineComponent* Spline = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Islands",
        meta = (ClampMin = "1", ClampMax = "8", UIMin = "1", UIMax = "8"))
    int32 NumIslands = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Islands")
    UStaticMesh* IslandMesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Islands")
    FVector IslandScale = FVector(1.f, 1.f, 1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float MoveSpeed = 200.0f;

private:
    float SplineLength = 0.0f;

    float BaseDistance = 0.0f;

    UPROPERTY()
    TArray<UStaticMeshComponent*> IslandMeshes;

    TArray<float> IslandOffsets;
};
