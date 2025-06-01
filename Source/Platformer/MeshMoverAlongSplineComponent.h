#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "MeshMoverAlongSplineComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLATFORMER_API UMeshMoverAlongSplineComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UMeshMoverAlongSplineComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Movement")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Movement")
	float StartAtProgress = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline Movement")
	float CurrentProgress = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Movement")
	float MovementSpeed = 100.0f;

private:
	float TimeSinceStarted = 0.0f;
};
