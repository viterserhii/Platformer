#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDeathVolume.generated.h"

class UBoxComponent;
class AMyCharacter;

UCLASS()
class PLATFORMER_API ABaseDeathVolume : public AActor
{
    GENERATED_BODY()

public:
    ABaseDeathVolume();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* CollisionBox;

    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    virtual void HandleCharacterEnter(class AMyCharacter* Character);
};
