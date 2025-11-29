#include "Pickups/LivesPickup.h"
#include "Game/MyPlayerState.h"
#include "Player/MyCharacter.h"

void ALivesPickup::OnPickedUp(AMyCharacter* Character)
{
    if (!Character)
    {
        return;
    }

    AMyPlayerState* PS = Character->GetPlayerState<AMyPlayerState>();
	if (PS)
    {
        PS->AddLive();
    }
	Super::OnPickedUp(Character);
}
