#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Logging/LogMacros.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(config = Game)
class PLATFORMER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;


public:
	AMyCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void FellOutOfWorld(const UDamageType& DmgType) override;

	UFUNCTION(BlueprintCallable)
	void Die();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Life")
	float MaxHealth = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Life")
	float Health = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Life")
	bool bIsDead = false;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
