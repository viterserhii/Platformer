#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

UCLASS()
class PLATFORMER_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMyPlayerState();

	UFUNCTION(BlueprintCallable, Category = "Coins")
	void AddCoin();

	UFUNCTION(BlueprintCallable, Category = "Lives")
	void AddLive();

	UFUNCTION(BlueprintCallable, Category = "Lives")
	void RemoveLive();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coins")
	int32 Coins = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lives")
	int32 LivesOnStart = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lives")
	int32 MaxLives = 99;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lives")
	int32 Lives = LivesOnStart;
};
