#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ElectricalInterface.generated.h"

UINTERFACE(MinimalAPI)
class UElectricalInterface : public UInterface
{
	GENERATED_BODY()
};

class INTERACTIONSYSTEM_API IElectricalInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Electrical")
	void Activate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Electrical")
	void Deactivate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Electrical")
	bool IsActive() const;
};
