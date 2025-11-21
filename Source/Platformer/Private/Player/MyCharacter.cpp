#include "Player/MyCharacter.h"
#include "Game/MyGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f; 
    SpringArm->bUsePawnControlRotation = true; 

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); 
    Camera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true; 
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void AMyCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}


//////////////////////////////////////////////////////////////////////////
// Input

void AMyCharacter::NotifyControllerChanged()
{
    Super::NotifyControllerChanged();

    // Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMyCharacter::Sprint);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // get right vector 
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // add movement 
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AMyCharacter::Sprint(const FInputActionValue& Value)
{
    bool ShouldSprint = Value.Get<bool>();

    if (ShouldSprint)
    {
        if (GetCharacterMovement()->IsMovingOnGround())
        {
            GetCharacterMovement()->MaxWalkSpeed = 800.0f;
        }
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    }
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AMyCharacter::FellOutOfWorld(const UDamageType& DmgType)
{
    Die();
}

float AMyCharacter::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    if (bIsDead || DamageAmount <= 0.f) return 0.f;

    Health -= DamageAmount;
    if (Health <= 0.f)
    {
        Health = 0.f;
        Die();
    }
    return DamageAmount;
}

void AMyCharacter::Die()
{
    if (bIsDead) return;
    bIsDead = true;

    if (auto* Move = GetCharacterMovement())
    {
        Move->StopMovementImmediately();
    }
    DisableInput(Cast<APlayerController>(GetController()));

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (AMyGameMode* GM = GetWorld()->GetAuthGameMode<AMyGameMode>())
        {
            GM->Respawn(PC);
            return;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Die(): Respawn couldn't be triggered"));
}