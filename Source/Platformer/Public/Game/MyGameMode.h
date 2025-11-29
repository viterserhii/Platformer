#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

class AMyCharacter;
class ACheckpoint;
class AMyPlayerState;

UCLASS()
class PLATFORMER_API AMyGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyGameMode();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void Respawn(AController* Controller);

    UFUNCTION(BlueprintCallable)
    void HandlePlayerDeath(AController* Controller);

    void SetCurrentCheckpoint(ACheckpoint* NewCheckpoint);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Respawn")
    TSubclassOf<AMyCharacter> CharacterClass;

private:
    UPROPERTY()
    ACheckpoint* CurrentCheckpoint = nullptr;

    FTransform DefaultSpawnTransform;
};
