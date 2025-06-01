#include "Checkpoint.h"

ACheckpoint::ACheckpoint()
{
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetupAttachment(RootComponent);
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBeginOverlap);

    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
    SpriteComponent->SetupAttachment(RootComponent);

    Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    Arrow->SetupAttachment(RootComponent);

    TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
    TextComponent->SetupAttachment(RootComponent);

    AdditionalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AdditionalMeshComponent"));
    AdditionalMeshComponent->SetupAttachment(RootComponent);

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);
    AudioComponent->bAutoActivate = false;

    DynamicMaterialInstance = CreateDefaultSubobject<UMaterialInstanceDynamic>(TEXT("DynamicMaterialInstance"));

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("MaterialInterface'/Game/Hour_of_Code/Materials/MI_Checkpoint.MI_Checkpoint'"));
    if (MaterialFinder.Succeeded())
    {
        BaseMaterial = MaterialFinder.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not load the material"));
    }
}

void ACheckpoint::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (BaseMaterial != nullptr)
    {
        DynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
        if (MeshComponent && DynamicMaterialInstance)
        {
            MeshComponent->SetMaterial(0, DynamicMaterialInstance);
        }
    }
}

void ACheckpoint::BeginPlay()
{
    Super::BeginPlay();

    if (MeshComponent && DynamicMaterialInstance)
    {
        MeshComponent->SetMaterial(0, DynamicMaterialInstance);
    }
}

void ACheckpoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        UpdateSpawnTransform(GetActorTransform());
    }

    if (DynamicMaterialInstance)
    {
        DynamicMaterialInstance->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
    }

    if (AudioComponent && SoundToPlay)
    {
        AudioComponent->SetSound(SoundToPlay);
        AudioComponent->Play();
    }
}


void ACheckpoint::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

