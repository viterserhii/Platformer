#include "World/Checkpoint.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Game/MyGameMode.h"

ACheckpoint::ACheckpoint()
{
    PrimaryActorTick.bCanEverTick = false;

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    SetRootComponent(Collision);
    Collision->InitSphereRadius(80.f);
    Collision->SetCollisionObjectType(ECC_WorldDynamic);
    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
    Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    Arrow->SetupAttachment(RootComponent);

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    BaseMesh->SetupAttachment(RootComponent);

    ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
    ButtonMesh->SetupAttachment(RootComponent);

    Collision->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBeginOverlap);
}

void ACheckpoint::BeginPlay()
{
    Super::BeginPlay();

    if (DefaultMaterial && ButtonMesh)
    {
        ButtonMesh->SetMaterial(0, DefaultMaterial);
    }
}

void ACheckpoint::OnBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (bIsActivated)
        return;

    ACharacter* PlayerChar = Cast<ACharacter>(OtherActor);
    if (!PlayerChar)
        return;

    if (AMyGameMode* GM = GetWorld()->GetAuthGameMode<AMyGameMode>())
    {
        GM->SetCurrentCheckpoint(this);
    }
}

void ACheckpoint::ActivateCheckpoint()
{
    bIsActivated = true;

    if (ActivateSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, ActivateSound, GetActorLocation());
    }

    if (ButtonActiveMaterial && ButtonMesh)
    {
        ButtonMesh->SetMaterial(0, ButtonActiveMaterial);
    }
}

void ACheckpoint::DeactivateCheckpoint()
{
    bIsActivated = false;

    if (DefaultMaterial && ButtonMesh)
    {
        ButtonMesh->SetMaterial(0, DefaultMaterial);
    }
}

FTransform ACheckpoint::GetSpawnTransform() const
{
    return Arrow ? Arrow->GetComponentTransform() : GetActorTransform();
}
