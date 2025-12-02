#include "ElectricalActor.h"

AElectricalActor::AElectricalActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

bool AElectricalActor::CanActivate() const
{
    if (PrerequisiteActors.Num() == 0)
    {
        return true;
    }

    for (AActor* Actor : PrerequisiteActors)
    {
        if (!IsValid(Actor))
        {
            return false;
        }

        if (!Actor->GetClass()->ImplementsInterface(UElectricalInterface::StaticClass()))
        {
            return false;
        }

        if (!IElectricalInterface::Execute_IsActive(Actor))
        {
            return false;
        }
    }

    return true;
}

void AElectricalActor::Activate_Implementation()
{
    if (State == EElectricalState::Active)
    {
        return;
    }

    if (!CanActivate())
    {
        State = EElectricalState::ReadyToActivate;
        return;
    }

    State = EElectricalState::Active;

    for (AActor* Actor : ActorsToActivate)
    {
        if (!IsValid(Actor)) continue;

        if (Actor->GetClass()->ImplementsInterface(UElectricalInterface::StaticClass()))
        {
            IElectricalInterface::Execute_Activate(Actor);
        }
    }
}

void AElectricalActor::Deactivate_Implementation()
{
    if (State == EElectricalState::Inactive)
    {
        return;
    }

    State = EElectricalState::Inactive;

    for (AActor* Actor : ActorsToActivate)
    {
        if (!IsValid(Actor)) continue;

        if (Actor->GetClass()->ImplementsInterface(UElectricalInterface::StaticClass()))
        {
            IElectricalInterface::Execute_Deactivate(Actor);
        }
    }
}

bool AElectricalActor::IsActive_Implementation() const
{
    return State == EElectricalState::Active;
}
