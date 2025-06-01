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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<class AMyCharacter> CharacterClass;

private:
	FVector SpawnLocation;
	FRotator SpawnRotation;
};
