#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class PLATFORMER_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoin();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Coin")
	USphereComponent * CoinCollision = nullptr;	

	UPROPERTY(VisibleAnywhere, Category = "Coin")
	UStaticMeshComponent* CoinMesh = nullptr;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
