#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "CoinPickup.generated.h"

UCLASS()
class PLATFORMER_API ACoinPickup : public APickupBase
{
	GENERATED_BODY()

protected:
	virtual void OnPickedUp(AMyCharacter* Character) override;
	
};
