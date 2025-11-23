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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coins")
	int32 Coins = 0;
	
};
