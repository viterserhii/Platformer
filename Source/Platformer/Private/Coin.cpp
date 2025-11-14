#include "Coin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameMode.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;

    CoinCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    SetRootComponent(CoinCollision);
    CoinCollision->InitSphereRadius(80.f);
    CoinCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CoinCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    CoinCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
    CoinMesh->SetupAttachment(RootComponent);

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
            Destroy();
        }
    }
}
