#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElectricalInterface.h"
#include "ElectricalActor.generated.h"

UENUM(BlueprintType)
enum class EElectricalState : uint8
{
    Inactive        UMETA(DisplayName = "Inactive"),
    ReadyToActivate UMETA(DisplayName = "Ready To Activate"),
    Active          UMETA(DisplayName = "Active")
};

UCLASS()
class INTERACTIONSYSTEM_API AElectricalActor : public AActor, public IElectricalInterface
{
    GENERATED_BODY()

public:
    AElectricalActor();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Electrical")
    EElectricalState State = EElectricalState::Inactive;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Electrical")
    TArray<AActor*> PrerequisiteActors;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Electrical")
    TArray<AActor*> ActorsToActivate;

public:
    virtual void Activate_Implementation() override;
    virtual void Deactivate_Implementation() override;
    virtual bool IsActive_Implementation() const override;

    UFUNCTION(BlueprintCallable, Category = "Electrical")
    bool CanActivate() const;

    UFUNCTION(BlueprintCallable, Category = "Electrical")
    EElectricalState GetState() const { return State; }

    UFUNCTION(BlueprintCallable, Category = "Electrical")
    void SetState(EElectricalState NewState) { State = NewState; }
};
