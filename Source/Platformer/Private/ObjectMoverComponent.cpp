#include "ObjectMoverComponent.h"
#include "Kismet/KismetMathLibrary.h"

UObjectMoverComponent::UObjectMoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TargetPoint = FVector (0.f, 0.f, 0.f);
	Speed = 200.0f;
	PauseDuration = 0.0f;
	EasingType = EEasingType::Linear;
	bIsMoving = false;
	CurrentPauseTime = 0.0f;
	bMovingToTarget = true;
	CurrentTime = 0.0f;
}


void UObjectMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetOwner()->GetActorLocation();
	CurrentTargetPoint = TargetPoint;
	CurrentPauseTime = PauseDuration;
	bIsMoving = false;
}

void UObjectMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsMoving)
	{
		CurrentPauseTime -= DeltaTime;
		if (CurrentPauseTime <= 0.0f)
		{
			bIsMoving = true;
			CurrentTime = 0.0f;
		}
		return;
	}


	FVector StartLocation = bMovingToTarget ? StartPoint : TargetPoint;
	FVector EndLocation = bMovingToTarget ? TargetPoint : StartPoint;

	float JourneyLength = FVector::Distance(StartLocation, EndLocation);
	CurrentTime += DeltaTime * Speed / JourneyLength;

	float Alpha = FMath::Clamp(CurrentTime, 0.0f, 1.0f);

	switch (EasingType)
	{
	case EEasingType::QuadraticInOut:
		Alpha = FMath::InterpEaseInOut(0.0f, 1.0f, Alpha, 2.0f);
		break;
	default:
		break;
	}

	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);
	GetOwner()->SetActorLocation(NewLocation);

	if (Alpha >= 1.0f)
	{
		bIsMoving = false;
		CurrentPauseTime = PauseDuration;

		bMovingToTarget = !bMovingToTarget;
		CurrentTime = 0.0f;
	}

}

