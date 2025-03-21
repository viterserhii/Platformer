#include "MyGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

AMyGameMode::AMyGameMode()
{

}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	AActor* PlayerStart = UGameplayStatics::GetActorOfClass(this, APlayerStart::StaticClass());
	if (PlayerStart)
	{
		SpawnLocation = PlayerStart->GetActorLocation();
	}
}

void AMyGameMode::Respawn(AController* Controller)
{
    if (!Controller || !CharacterClass) return;

    if (APawn* OldPawn = Controller->GetPawn())
    {
        OldPawn->Destroy();
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AMyCharacter* NewPawn = GetWorld()->SpawnActor<AMyCharacter>(CharacterClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (NewPawn)
    {
        Controller->Possess(NewPawn);
    }
}
