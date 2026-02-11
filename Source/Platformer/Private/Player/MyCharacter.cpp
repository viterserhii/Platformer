#include "Player/MyCharacter.h"
#include "Game/MyGameMode.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"  
#include "Components/CapsuleComponent.h" 
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Engine/OverlapResult.h"
#include "TimerManager.h"   
#include "InteractionInterface.h"
#include "DrawDebugHelpers.h"

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

    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->bOrientRotationToMovement = true;
        MoveComp->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
        MoveComp->MaxWalkSpeed = 500.0f;
    }
}

void AMyCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMyCharacter::NotifyControllerChanged()
{
    Super::NotifyControllerChanged();

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMyCharacter::Sprint);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::Interact);
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AMyCharacter::Sprint(const FInputActionValue& Value)
{
    const bool bShouldSprint = Value.Get<bool>();

    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        if (bShouldSprint && MoveComp->IsMovingOnGround())
        {
            MoveComp->MaxWalkSpeed = 800.0f;
        }
        else
        {
            MoveComp->MaxWalkSpeed = 500.0f;
        }
    }
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AMyCharacter::FellOutOfWorld(const UDamageType& DmgType)
{
    Die();
}

void AMyCharacter::Die()
{
    if (bIsDying)
    {
        return;
    }
    bIsDying = true;

    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->StopMovementImmediately();
        MoveComp->DisableMovement();
    }

    if (UCapsuleComponent* Capsule = GetCapsuleComponent())
    {
        Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    if (USkeletalMeshComponent* MeshComp = GetMesh())
    {
        MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
        MeshComp->SetAllBodiesSimulatePhysics(true);
        MeshComp->SetSimulatePhysics(true);
        MeshComp->WakeAllRigidBodies();
        MeshComp->bBlendPhysics = true;
    }

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (PC->PlayerCameraManager)
        {
            PC->PlayerCameraManager->StartCameraFade(
                0.f, 
                1.f,   
                FadeDuration, 
                FLinearColor::Black,
                false,  
                true   
            );
        }
    }

    GetWorldTimerManager().SetTimer(
        RespawnTimerHandle,
        this,
        &AMyCharacter::OnDeathFinished,
        RespawnDelay,
        false
    );
}

void AMyCharacter::OnDeathFinished()
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC)
    {
        Destroy();
        return;
    }

    if (AMyGameMode* GM = GetWorld()->GetAuthGameMode<AMyGameMode>())
    {
        GM->HandlePlayerDeath(PC);

        if (PC->PlayerCameraManager)
        {
            PC->PlayerCameraManager->StartCameraFade(
                1.f,
                0.f,
                FadeDuration,
                FLinearColor::Black,
                false,
                false
            );
        }
        return;
    }

    Destroy();
}

void AMyCharacter::Interact(const FInputActionValue& Value)
{
    const FVector Center = GetActorLocation();
    const float   Radius = 150.f;

    TArray<FOverlapResult> Hits;

    FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->OverlapMultiByChannel(
        Hits,
        Center,
        FQuat::Identity,
        ECC_Visibility,
        Sphere,
        Params
    );

    if (!bHit)
    {
        return;
    }

    for (const FOverlapResult& Hit : Hits)
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor && HitActor->Implements<UInteractionInterface>())
        {
            IInteractionInterface::Execute_Interact(HitActor);
            break;
        }
    }

    DrawDebugSphere(GetWorld(), Center, Radius, 16, FColor::Green, false, 0.5f);
}
