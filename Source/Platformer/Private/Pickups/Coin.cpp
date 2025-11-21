#include "Pickups/Coin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Game/MyGameMode.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;

    CoinCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    SetRootComponent(CoinCollision);
    CoinCollision->InitSphereRadius(60.f);
    CoinCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CoinCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    CoinCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
    CoinMesh->SetupAttachment(RootComponent);

    RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
    RotatingComponent->RotationRate = FRotator(0, 180, 0);

    CoinCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBeginOverlap);
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        APawn* PlayerPawn = Cast<APawn>(OtherActor);
        if (PlayerPawn)
        {
            if (AMyGameMode* GM = GetWorld()->GetAuthGameMode<AMyGameMode>())
            {
                GM->AddCoin();
            }
            if (CollectSound)
            {
                UGameplayStatics::PlaySoundAtLocation(this, CollectSound, GetActorLocation());
			}
            Destroy();
        }
    }
}
