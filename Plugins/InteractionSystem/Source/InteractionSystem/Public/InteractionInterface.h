#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UINTERFACE(Blueprintable)
class INTERACTIONSYSTEM_API UInteractionInterface : public UInterface
{
    GENERATED_BODY()
};

class INTERACTIONSYSTEM_API IInteractionInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Interact();
};
