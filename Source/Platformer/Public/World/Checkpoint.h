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

    UPROPERTY(VisibleDefaultsOnly, Category = "Components")
    USphereComponent* Collision = nullptr;

    UPROPERTY(VisibleDefaultsOnly, Category = "Components")
    UArrowComponent* Arrow = nullptr;

    UPROPERTY(VisibleDefaultsOnly, Category = "Components")
    UStaticMeshComponent* BaseMesh = nullptr;

    UPROPERTY(VisibleDefaultsOnly, Category = "Components")
    UStaticMeshComponent* ButtonMesh = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Checkpoint")
    UMaterialInterface* DefaultMaterial = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Checkpoint")
    UMaterialInterface* ButtonActiveMaterial = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Checkpoint")
    USoundBase* ActivateSound = nullptr;

    UPROPERTY(VisibleInstanceOnly, Category = "Checkpoint")
    bool bIsActivated = false;

    UFUNCTION()
    void OnBeginOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

public:

    UFUNCTION(BlueprintCallable)
    void ActivateCheckpoint();

    UFUNCTION(BlueprintCallable)
    void DeactivateCheckpoint();

    bool IsActivated() const { return bIsActivated; }

    FTransform GetSpawnTransform() const;
};
