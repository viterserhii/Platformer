#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

UCLASS()
class PLATFORMER_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameMode();	

	virtual void BeginPlay() override;

	UFUNCTION()
	void Respawn(AController* Controller);	

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void UpdateSpawnPoint(FVector NewLocation, FRotator NewRotation);

	UFUNCTION(BlueprintCallable, Category = "Coins")
	void AddCoin() { Coins++; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<class AMyCharacter> CharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coins")
	int32 Coins = 0;

private:
	FVector SpawnLocation;
	FRotator SpawnRotation;
};
