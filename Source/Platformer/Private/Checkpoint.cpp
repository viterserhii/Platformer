#include "Checkpoint.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "MyGameMode.h"

ACheckpoint::ACheckpoint()
{
    PrimaryActorTick.bCanEverTick = false;

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    SetRootComponent(Collision);
    Collision->InitSphereRadius(80.f);
    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
    Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    Arrow->SetupAttachment(RootComponent);

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    BaseMesh->SetupAttachment(RootComponent);
    BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
    ButtonMesh->SetupAttachment(RootComponent);
    ButtonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Collision->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBeginOverlap);
}

void ACheckpoint::BeginPlay()
{
    Super::BeginPlay();
}

void ACheckpoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (bActivated) return;
    if (!OtherActor || !OtherActor->IsA<ACharacter>()) return;

    if (AMyGameMode* GM = GetWorld()->GetAuthGameMode<AMyGameMode>())
    {
        GM->UpdateSpawnPoint(Arrow->GetComponentLocation(), Arrow->GetComponentRotation());
        bActivated = true;

        if (ActivateSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, ActivateSound, GetActorLocation());
        }

        if (ButtonActiveMaterial && ButtonMesh)
        {
            ButtonMesh->SetMaterial(0, ButtonActiveMaterial);
        }
    }
}


