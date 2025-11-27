#include "Game/MyPlayerState.h"
#include "Engine/Engine.h"

AMyPlayerState::AMyPlayerState()
{
}

void AMyPlayerState::AddCoin()
{
	Coins++;

GEngine->AddOnScreenDebugMessage(
		-1,
		1.5f,
		FColor::Yellow,
		FString::Printf(TEXT("Coins: %d"), Coins)
	);
}

void AMyPlayerState::AddLive()
{
    Lives = FMath::Clamp(Lives + 1, 0, MaxLives);

    GEngine->AddOnScreenDebugMessage(
        -1,
        1.5f,
        FColor::Red,
        FString::Printf(TEXT("Lives: %d"), Lives)
    );
}

void AMyPlayerState::RemoveLive()
{
    Lives = FMath::Clamp(Lives - 1, 0, MaxLives);

    GEngine->AddOnScreenDebugMessage(
        -1,
        1.5f,
        FColor::Red,
        FString::Printf(TEXT("Lives: %d"), Lives)
    );
}
