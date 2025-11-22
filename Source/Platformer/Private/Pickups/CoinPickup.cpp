#include "Pickups/CoinPickup.h"
#include "Game/MyPlayerState.h"
#include "Player/MyCharacter.h"

void ACoinPickup::OnPickedUp(AMyCharacter* Character)
{
    if (!Character)
    {
        return;
    }

    if (AMyPlayerState* PS = Character->GetPlayerState<AMyPlayerState>())
    {
        PS->AddCoin();
    }
}
