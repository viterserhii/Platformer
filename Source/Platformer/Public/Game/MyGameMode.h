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

	UFUNCTION()
	void Respawn(AController* Controller);

	void SetCurrentCheckpoint(ACheckpoint* NewCheckpoint);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<class AMyCharacter> CharacterClass;

private:
	UPROPERTY()
	ACheckpoint* CurrentCheckpoint = nullptr;

	UPROPERTY()
	ACheckpoint* PreviousCheckpoint = nullptr;

	FVector SpawnLocation;
	FRotator SpawnRotation;
};
