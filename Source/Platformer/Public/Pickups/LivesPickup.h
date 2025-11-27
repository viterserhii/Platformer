#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "LivesPickup.generated.h"

UCLASS()
class PLATFORMER_API ALivesPickup : public APickupBase
{
	GENERATED_BODY()

protected:
	virtual void OnPickedUp(AMyCharacter* Character) override;
	
};
