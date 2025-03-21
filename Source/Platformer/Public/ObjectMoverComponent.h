#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectMoverComponent.generated.h"

UENUM(BlueprintType)
enum class EEasingType : uint8
{
	Linear UMETA(DisplayName = "Linear"),
	QuadraticInOut UMETA(DisplayName = "Quadratic In-Out")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UObjectMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectMoverComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector TargetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float PauseDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EEasingType EasingType;

private:
	FVector StartPoint;
	FVector CurrentTargetPoint;
	float CurrentPauseTime;
	float CurrentTime;
	bool bIsMoving;
	bool bMovingToTarget;
		
};
