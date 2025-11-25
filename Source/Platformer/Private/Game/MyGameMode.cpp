#include "Game/MyGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyCharacter.h"
#include "Game/MyPlayerState.h"
#include "World/Checkpoint.h"

AMyGameMode::AMyGameMode()
{
    PlayerStateClass = AMyPlayerState::StaticClass();
}

void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Беремо трансформ PlayerStart як дефолтну точку респавну
    if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass(this, APlayerStart::StaticClass()))
    {
        DefaultSpawnTransform = PlayerStart->GetActorTransform();
    }
}

void AMyGameMode::SetCurrentCheckpoint(ACheckpoint* NewCheckpoint)
{
    if (!NewCheckpoint) return;

    // Деактивуємо старий чекпоінт
    if (CurrentCheckpoint)
    {
        CurrentCheckpoint->DeactivateCheckpoint();
    }

    // Активуємо новий
    CurrentCheckpoint = NewCheckpoint;
    CurrentCheckpoint->ActivateCheckpoint();
}

void AMyGameMode::Respawn(AController* Controller)
{
    if (!Controller || !CharacterClass) return;

    // Визначаємо трансформ для респавну:
    const FTransform SpawnTransform =
        CurrentCheckpoint ? CurrentCheckpoint->GetSpawnTransform()
        : DefaultSpawnTransform;

    // Видаляємо старого персонажа (якщо є)
    if (APawn* OldPawn = Controller->GetPawn())
    {
        OldPawn->Destroy();
    }

    // Спавнимо нового персонажа
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AMyCharacter* NewPawn = GetWorld()->SpawnActor<AMyCharacter>(
        CharacterClass,
        SpawnTransform.GetLocation(),
        SpawnTransform.GetRotation().Rotator(),
        SpawnParams
    );

    if (NewPawn)
    {
        Controller->Possess(NewPawn);
    }
}
