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

