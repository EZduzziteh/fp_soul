// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/MainPlayerController.h"
// MyPlayerController.cpp
#include "ui/Widget_Hud.h"

AMainPlayerController::AMainPlayerController() {
    APawn* MyPawn = GetPawn();
    if (!MyPawn) return;

    // Look for a camera component
    UCameraComponent* CameraComp = MyPawn->FindComponentByClass<UCameraComponent>();
    if (CameraComp)
    {
        // Only do camera setup if the component exists
        CameraComp->bUsePawnControlRotation = true;

        // Optionally, attach a spring arm if you want smooth camera movement
        USpringArmComponent* SpringArm = MyPawn->FindComponentByClass<USpringArmComponent>();
        if (SpringArm)
        {
            SpringArm->bUsePawnControlRotation = true;
        }
    }
}

void AMainPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // InputComponent is provided by APlayerController, no parameters needed
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (MoveAction)
        {
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
        }
        if (LookAction)
        {
            EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Look);
        }
        if (PrimaryAction)
        {
            EnhancedInput->BindAction(PrimaryAction, ETriggerEvent::Started, this, &AMainPlayerController::PrimaryStarted);
            EnhancedInput->BindAction(PrimaryAction, ETriggerEvent::Completed, this, &AMainPlayerController::PrimaryReleased);
        }
        if (JumpAction)
        {
            EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AMainPlayerController::JumpStarted);
        }
        if (SecondaryAction)
        {
            EnhancedInput->BindAction(SecondaryAction, ETriggerEvent::Started, this, &AMainPlayerController::SecondaryStarted);
            EnhancedInput->BindAction(SecondaryAction, ETriggerEvent::Completed, this, &AMainPlayerController::SecondaryReleased);
        }
        if (CastAction)
        {
            EnhancedInput->BindAction(CastAction, ETriggerEvent::Started, this, &AMainPlayerController::CastStarted);
            EnhancedInput->BindAction(CastAction, ETriggerEvent::Completed, this, &AMainPlayerController::CastReleased);
        }
        if (InteractAction)
        {
            EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainPlayerController::InteractStarted);
        }
        if (OpenInventoryAction)
        {
            EnhancedInput->BindAction(OpenInventoryAction, ETriggerEvent::Started, this, &AMainPlayerController::OpenInventoryStarted);
        }
    }
}

// Get last mouse direction
EMouseDirection AMainPlayerController::GetLastMouseDirection() const
{
    return LastMouseDirection;
}

void AMainPlayerController::Tick(float DeltaTime) {
    
    float DeltaX, DeltaY;
    GetInputMouseDelta(DeltaX, DeltaY);
    DetectMouseDirection(DeltaX, DeltaY);

    if (CameraComponent && GetCharacter())
    {
        // Get head socket transform in world space
       // FTransform HeadTransform = GetCharacter()->GetMesh()->GetSocketTransform(FName("head"), RTS_World);

        // Define offset relative to the head, like slightly behind and above

        // Transform local offset into world space
        //FVector CameraLocation = HeadTransform.TransformPosition(LocalOffset);

        // Apply location ONLY — rotation is handled by controller
       // CameraComponent->SetWorldLocation(CameraLocation);
    }
    if (!CameraComponent) return;

}

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();



    ControlledCombatCharacter = Cast<ACombatCharacter>(GetPawn());

    if (MyWidgetClass) // This is a UPROPERTY pointing to your Widget Blueprint
    {
        HUDWidget = CreateWidget<UWidget_Hud>(this, MyWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            HUDWidget->SetText(TEXT("Hello, Unreal UI!"));
        }
    }

  
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }

        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());
    

}






void AMainPlayerController::OpenInventoryWindow() {
    if (HUDWidget) {
        
        HUDWidget->ToggleInventoryWindow();
    }
}

void AMainPlayerController::OpenDialogueWindow(UTopicManagerComponent* topicManagerComponent) {
    if (HUDWidget) {

        HUDWidget->ToggleDialogueWindow(topicManagerComponent);
    }
}

void AMainPlayerController::DetectMouseDirection(float DeltaX, float DeltaY)
{
    //LastMouseDirection = EMouseDirection::None;
    LastMouseDirection = EMouseDirection::Up;
    if (FMath::Abs(DeltaX) < MouseMovementThreshold && FMath::Abs(DeltaY) < MouseMovementThreshold)
        return;

    float Angle = FMath::RadiansToDegrees(FMath::Atan2(DeltaY, DeltaX));
    if (Angle < 0) Angle += 360;

    //4 direction check
    if (Angle >= 315 || Angle < 45)
        LastMouseDirection = EMouseDirection::Right;
    else if (Angle < 135)
        LastMouseDirection = EMouseDirection::Up;
    else if (Angle < 225)
        LastMouseDirection = EMouseDirection::Left;
    else
        LastMouseDirection = EMouseDirection::Down;
    //8 direction checks
    /*
    if (Angle >= 337.5 || Angle < 22.5)
        LastMouseDirection = EMouseDirection::Right;
    else if (Angle < 67.5)
        LastMouseDirection = EMouseDirection::UpRight;
    else if (Angle < 112.5)
        LastMouseDirection = EMouseDirection::Up;
    else if (Angle < 157.5)
        LastMouseDirection = EMouseDirection::UpLeft;
    else if (Angle < 202.5)
        LastMouseDirection = EMouseDirection::Left;
    else if (Angle < 247.5)
        LastMouseDirection = EMouseDirection::DownLeft;
    else if (Angle < 292.5)
        LastMouseDirection = EMouseDirection::Down;
    else
        LastMouseDirection = EMouseDirection::DownRight;
        */

        // UE_LOG(LogTemp, Log, TEXT("Mouse moved: %s"), *UEnum::GetValueAsString(LastMouseDirection));
}

// Movement input
void AMainPlayerController::Move(const FInputActionValue& Value)
{
    FVector2D Input = Value.Get<FVector2D>();

    DetectMovementDirection(Input);

    if ( (Input.X != 0.f || Input.Y != 0.f))
    {
       // const FRotator ControlRotation = GetControlRotation();
        const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        ControlledCombatCharacter->AddMovementInput(ForwardDirection, Input.Y);
        ControlledCombatCharacter->AddMovementInput(RightDirection, Input.X);
    }
}

void AMainPlayerController::Look(const FInputActionValue& Value)
{
    FVector2D LookAxis = Value.Get<FVector2D>();
    AddYawInput(LookAxis.X * HorizontalSensitivity);
    AddPitchInput(LookAxis.Y * VerticalSensitivity);

    // Update LookPitch from controller
    ControlledCombatCharacter->LookPitch = GetControlRotation().Pitch;
}
void AMainPlayerController::DetectMovementDirection(FVector2D Input)
{
    if (Input.IsNearlyZero())
    {
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::None;
        return;
    }

    float Angle = FMath::RadiansToDegrees(FMath::Atan2(Input.Y, Input.X));
    if (Angle < 0) Angle += 360;

    if (Angle >= 337.5 || Angle < 22.5)
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::Right;
    else if (Angle < 67.5)
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::UpRight;
    else if (Angle < 112.5)
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::Up;
    else if (Angle < 157.5)
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::UpLeft;
    else if (Angle < 202.5)
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::Left;
    else if (Angle < 247.5)
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::DownLeft;
    else if (Angle < 292.5)
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::Down;
    else
        ControlledCombatCharacter->LastMoveDirection = EMoveDirection::DownRight;
}
void AMainPlayerController::JumpStarted(const FInputActionValue& Value)
{
    ControlledCombatCharacter->Jump(); // This uses the default Character jump behavior and preserves horizontal movement
}

void AMainPlayerController::PrimaryStarted(const FInputActionValue& Value)
{
    if (!ControlledCombatCharacter->PrimaryAvailable) return;

    ControlledCombatCharacter->ActionState = EActionState::StartAttack;
    ControlledCombatCharacter->AttackDirection = GetLastMouseDirection();
}

void AMainPlayerController::PrimaryReleased(const FInputActionValue& Value)
{
    if (!ControlledCombatCharacter->PrimaryAvailable) return;

    ControlledCombatCharacter->ActionState = EActionState::ReleaseAttack;
    if (ControlledCombatCharacter->GetMesh() && ControlledCombatCharacter->GetMesh()->GetAnimInstance())
    {
        if (UAnimMontage* Montage = ControlledCombatCharacter->GetAttackMontage())
        {
            ControlledCombatCharacter->GetMesh()->GetAnimInstance()->Montage_Play(Montage);
        }
    }
}


void AMainPlayerController::SecondaryStarted(const FInputActionValue& Value)
{

    GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("Secondary started")));
}
void AMainPlayerController::SecondaryReleased(const FInputActionValue& Value)
{

    GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("Secondary released")));
}

void AMainPlayerController::CastStarted(const FInputActionValue& Value)
{

    ControlledCombatCharacter->ActionState = EActionState::StartCast;
}
void AMainPlayerController::CastReleased(const FInputActionValue& Value)
{
    ControlledCombatCharacter->ActionState = EActionState::ReleaseCast;
    if (ControlledCombatCharacter->GetMesh() && ControlledCombatCharacter->GetMesh()->GetAnimInstance()) {
        ControlledCombatCharacter->GetMesh()->GetAnimInstance()->Montage_Play(ControlledCombatCharacter->GetSpellMontage());
    }

}
void AMainPlayerController::InteractStarted(const FInputActionValue& Value)
{
    if (ControlledCombatCharacter->CurrentInteractable && ControlledCombatCharacter->CurrentInteractable->Implements<UInteractable>())
    {
        if (ControlledCombatCharacter->CurrentInteractable && ControlledCombatCharacter->CurrentInteractable->Implements<UInteractable>())
        {
            GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("try interact")));
            UE_LOG(LogTemp, Log, TEXT("trying interact"));
            IInteractable::Execute_HandleInteraction(ControlledCombatCharacter->CurrentInteractable, this);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("no interactable")));
            UE_LOG(LogTemp, Log, TEXT("no interactable"));
        }
    }
    else {

        GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("no interactable or doesnt implement uinteractable")));
    }
}

void AMainPlayerController::OpenInventoryStarted(const FInputActionValue& Value)
{
    OpenInventoryWindow();
}

