#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

class AMyCharacter;
class ACheckpoint;

UCLASS()
class PLATFORMER_API AMyGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyGameMode();

    virtual void BeginPlay() override;

    /** Респавн гравця у правильному місці */
    UFUNCTION(BlueprintCallable)
    void Respawn(AController* Controller);

    /** Встановлюємо активний чекпоінт */
    void SetCurrentCheckpoint(ACheckpoint* NewCheckpoint);

protected:
    /** Клас персонажа для респавну */
    UPROPERTY(EditDefaultsOnly, Category = "Respawn")
    TSubclassOf<AMyCharacter> CharacterClass;

private:
    /** Останній активний чекпоінт */
    UPROPERTY()
    ACheckpoint* CurrentCheckpoint = nullptr;

    /** Трансформ стартової точки (PlayerStart) */
    FTransform DefaultSpawnTransform;
};
