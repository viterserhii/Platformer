#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USoundBase;
class AMyCharacter;
class URotatingMovementComponent;

UCLASS()
class PLATFORMER_API APickupBase : public AActor
{
    GENERATED_BODY()

public:
    APickupBase();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
    USphereComponent* Collision = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
    UStaticMeshComponent* Mesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
    URotatingMovementComponent* RotatingComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    USoundBase* PickupSound = nullptr;

    virtual void OnPickedUp(AMyCharacter* Character);

private:
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
