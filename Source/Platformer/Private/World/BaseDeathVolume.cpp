#include "World/BaseDeathVolume.h"
#include "Components/BoxComponent.h"
#include "Player/MyCharacter.h"

ABaseDeathVolume::ABaseDeathVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    SetRootComponent(CollisionBox);

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ABaseDeathVolume::BeginPlay()
{
    Super::BeginPlay();

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseDeathVolume::OnOverlapBegin);
}

void ABaseDeathVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
    {
        HandleCharacterEnter(Character);
    }
}

void ABaseDeathVolume::HandleCharacterEnter(AMyCharacter* Character)
{
    if (Character)
    {
        Character->Die();
    }
}
