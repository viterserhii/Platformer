#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UArrowComponent;
class USoundBase;
class UMaterialInterface;

UCLASS()
class PLATFORMER_API ACheckpoint : public AActor
{
    GENERATED_BODY()

public:
    ACheckpoint();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Collision = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UArrowComponent* Arrow = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* BaseMesh = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* ButtonMesh = nullptr;

    UPROPERTY(EditAnywhere, Category = "Checkpoint")
    UMaterialInterface* ButtonActiveMaterial = nullptr;

    UPROPERTY(EditAnywhere, Category = "Checkpoint")
    USoundBase* ActivateSound = nullptr;

    bool bActivated = false;

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
