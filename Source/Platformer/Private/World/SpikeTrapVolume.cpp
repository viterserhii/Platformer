#include "World/SpikeTrapVolume.h"
#include "Components/StaticMeshComponent.h"
#include "Player/MyCharacter.h"

ASpikeTrapVolume::ASpikeTrapVolume()
{
    FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
    FloorMesh->SetupAttachment(RootComponent);

    SpikesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikesMesh"));
    SpikesMesh->SetupAttachment(FloorMesh);
}

void ASpikeTrapVolume::HandleCharacterEnter(AMyCharacter* Character)
{
    RaiseAndLowerSpikes(); 

    if (Character)
    {
        Character->Die();
    }
}
