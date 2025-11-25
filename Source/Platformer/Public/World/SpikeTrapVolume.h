#pragma once

#include "CoreMinimal.h"
#include "World/BaseDeathVolume.h"
#include "SpikeTrapVolume.generated.h"

class UStaticMeshComponent;
class AMyCharacter;

UCLASS()
class PLATFORMER_API ASpikeTrapVolume : public ABaseDeathVolume
{
    GENERATED_BODY()

public:
    ASpikeTrapVolume();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* FloorMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* SpikesMesh;

    virtual void HandleCharacterEnter(AMyCharacter* Character) override;

    UFUNCTION(BlueprintImplementableEvent, Category = "SpikeTrap")
    void RaiseAndLowerSpikes();
};
