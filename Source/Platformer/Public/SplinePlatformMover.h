#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePlatformMover.generated.h"

class USplineComponent;
class UStaticMeshComponent;

UCLASS()
class PLATFORMER_API ASplinePlatformMover : public AActor
{
	GENERATED_BODY()
	
public:	
	ASplinePlatformMover();

public:	
	virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline")
    USplineComponent* Spline;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline")
    UStaticMeshComponent* PlatformMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
    float MoveSpeed = 200.0f;

private:
    float CurrentDistance = 0.0f;
    float SplineLength = 0.0f;
};
