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
		SpawnRotation = PlayerStart->GetActorRotation();
	}
}

void AMyGameMode::UpdateSpawnPoint(FVector NewLocation, FRotator NewRotation)
{
    SpawnLocation = NewLocation;
    SpawnRotation = NewRotation;
}

void AMyGameMode::AddCoin()
{
	Coins++;

	GEngine->AddOnScreenDebugMessage(
		-1,
		1.5f,
		FColor::Yellow,
		FString::Printf(TEXT("Coins: %d"), Coins)
	);
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

    AMyCharacter* NewPawn = GetWorld()->SpawnActor<AMyCharacter>(CharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
    if (NewPawn)
    {
        Controller->Possess(NewPawn);
    }
}
