#include "Pickups/CoinPickup.h"
#include "Game/MyGameMode.h" //PlayerState
#include "Player/MyCharacter.h"

void ACoinPickup::OnPickedUp(AMyCharacter* Character)
{
	if (AMyGameMode* GM = GetWorld()->GetAuthGameMode<AMyGameMode>())
	{
		GM->AddCoin();
	}
}
