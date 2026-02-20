#include "CombatCharacter.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AsyncRootMovement.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "../../../Plugins/RootMovement/Source/RootMovement/Public/AsyncRootMovement.h"
ACombatCharacter::ACombatCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = true;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;

    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
    SpellbookComponent = CreateDefaultSubobject<USpellbookComponent>(TEXT("SpellbookComponent"));
    StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));;
    EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent")); 
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(RootComponent); // Or to mesh if needed
    CameraComponent->bUsePawnControlRotation = true;
    MeleeTraceComponent = CreateDefaultSubobject<UMeleeTraceComponent>(TEXT("MeleeTraceComponent"));

    PrimaryWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PrimaryWeapon"));
    PrimaryWeapon->SetupAttachment(GetMesh(), FName("Item_R")); // Replace with appropriate socket
    PrimaryWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PrimaryWeapon->SetOnlyOwnerSee(false);
    PrimaryWeapon->bCastDynamicShadow = true;
    PrimaryWeapon->CastShadow = true;

    SecondaryWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SecondaryWeapon"));
    SecondaryWeapon->SetupAttachment(GetMesh(), FName("Item_L")); // Replace with appropriate socket
    SecondaryWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SecondaryWeapon->SetOnlyOwnerSee(false);
    SecondaryWeapon->bCastDynamicShadow = true;
    SecondaryWeapon->CastShadow = true;

    GetMesh()->SetOwnerNoSee(true);

}

void ACombatCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
}

void ACombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACombatCharacter::Move);
        }
        if (LookAction)
        {
            EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACombatCharacter::Look);
        }
        if (PrimaryAction)
        {
            EnhancedInput->BindAction(PrimaryAction, ETriggerEvent::Started, this, &ACombatCharacter::PrimaryStarted);
            EnhancedInput->BindAction(PrimaryAction, ETriggerEvent::Completed, this, &ACombatCharacter::PrimaryReleased);
        }
        if (PrimaryAction)
        {
            EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACombatCharacter::JumpStarted);
        }
        if (SecondaryAction)
        {
            EnhancedInput->BindAction(SecondaryAction, ETriggerEvent::Started, this, &ACombatCharacter::SecondaryStarted);
            EnhancedInput->BindAction(SecondaryAction, ETriggerEvent::Completed, this, &ACombatCharacter::SecondaryReleased);
        } 
        
        if (CastAction)
        {
            EnhancedInput->BindAction(CastAction, ETriggerEvent::Started, this, &ACombatCharacter::CastStarted);
            EnhancedInput->BindAction(CastAction, ETriggerEvent::Completed, this, &ACombatCharacter::CastReleased);
        }

        if (InteractAction)
        {
            EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &ACombatCharacter::InteractStarted);
            EnhancedInput->BindAction(InteractAction, ETriggerEvent::Completed, this, &ACombatCharacter::InteractReleased);
        }
    }
}


void ACombatCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        float DeltaX, DeltaY;
        PC->GetInputMouseDelta(DeltaX, DeltaY);
        DetectMouseDirection(DeltaX, DeltaY);
    }

    // --- Interactable trace logic ---
    const float TraceDistance = 300.f;
    const float TraceRadius = 30.f;
    if (CameraComponent && GetMesh())
    {
        // Get head socket transform in world space
        FTransform HeadTransform = GetMesh()->GetSocketTransform(FName("head"), RTS_World);

        // Define offset relative to the head, like slightly behind and above

        // Transform local offset into world space
        FVector CameraLocation = HeadTransform.TransformPosition(LocalOffset);

        // Apply location ONLY — rotation is handled by controller
        CameraComponent->SetWorldLocation(CameraLocation);
    }
    if (!CameraComponent) return;

    FVector Start = CameraComponent->GetComponentLocation();
    FVector End = Start + (CameraComponent->GetForwardVector() * TraceDistance);

    FCollisionShape Sphere = FCollisionShape::MakeSphere(TraceRadius);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->SweepSingleByChannel(
        Hit,
        Start,
        End,
        FQuat::Identity,
        ECC_Visibility,
        Sphere,
        Params
    );

    if (bHit && Hit.GetActor())
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor->Implements<UInteractable>())
        {
            CurrentInteractable = HitActor;
            if (IsValid(this) && HasAuthority())
            {
                SetInteractionMessage(TEXT("Press E to Interact with ") + CurrentInteractable->GetName());
            }
        }
        else
        {
            if (IsValid(this) && HasAuthority())
            {
                SetInteractionMessage(TEXT(""));
            }
            CurrentInteractable = nullptr;
        }
    }
    else
    {
        if (IsValid(this) && HasAuthority())
        {
            SetInteractionMessage(TEXT(""));
        }
        CurrentInteractable = nullptr;
    }
}


void ACombatCharacter::DetectMouseDirection(float DeltaX, float DeltaY)
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

    UE_LOG(LogTemp, Log, TEXT("Mouse moved: %s"), *UEnum::GetValueAsString(LastMouseDirection));
}

// Movement input
void ACombatCharacter::Move(const FInputActionValue& Value)
{
    FVector2D Input = Value.Get<FVector2D>();

    DetectMovementDirection(Input);

    if (Controller && (Input.X != 0.f || Input.Y != 0.f))
    {
        const FRotator ControlRotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, Input.Y);
        AddMovementInput(RightDirection, Input.X);
    }
}

void ACombatCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxis = Value.Get<FVector2D>();
    AddControllerYawInput(LookAxis.X * HorizontalSensitivity);
    AddControllerPitchInput(LookAxis.Y * VerticalSensitivity);

    // Update LookPitch from controller
    FRotator ControlRotation = Controller->GetControlRotation();
    LookPitch = ControlRotation.Pitch;
}
void ACombatCharacter::DetectMovementDirection(FVector2D Input)
{
    if (Input.IsNearlyZero())
    {
        LastMoveDirection = EMoveDirection::None;
        return;
    }

    float Angle = FMath::RadiansToDegrees(FMath::Atan2(Input.Y, Input.X));
    if (Angle < 0) Angle += 360;

    if (Angle >= 337.5 || Angle < 22.5)
        LastMoveDirection = EMoveDirection::Right;
    else if (Angle < 67.5)
        LastMoveDirection = EMoveDirection::UpRight;
    else if (Angle < 112.5)
        LastMoveDirection = EMoveDirection::Up;
    else if (Angle < 157.5)
        LastMoveDirection = EMoveDirection::UpLeft;
    else if (Angle < 202.5)
        LastMoveDirection = EMoveDirection::Left;
    else if (Angle < 247.5)
        LastMoveDirection = EMoveDirection::DownLeft;
    else if (Angle < 292.5)
        LastMoveDirection = EMoveDirection::Down;
    else
        LastMoveDirection = EMoveDirection::DownRight;
}

// Get last mouse direction
EMouseDirection ACombatCharacter::GetLastMouseDirection() const
{
    return LastMouseDirection;
}

// Get last mouse direction
EMoveDirection ACombatCharacter::GetLastMoveDirection() const
{
    return LastMoveDirection;
}

void ACombatCharacter::SetInteractionMessage_Implementation(const FString& Message)
{
    if (GEngine)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, Message);
    }
}
void ACombatCharacter::JumpStarted(const FInputActionValue& Value)
{
    Jump(); // This uses the default Character jump behavior and preserves horizontal movement
}

void ACombatCharacter::PrimaryStarted(const FInputActionValue& Value)
{
    if (!PrimaryAvailable) return;

    ActionState = EActionState::StartAttack;
    AttackDirection = GetLastMouseDirection();
}

void ACombatCharacter::InterruptPrimaryAttack_Implementation()
{
    // Stop primary attack logic
    PrimaryAvailable = true;
    ActionState = EActionState::None;

    if (GetMesh() && GetMesh()->GetAnimInstance())
    {
        GetMesh()->GetAnimInstance()->StopAllMontages(0.2f);
    }

    // Call the event
    OnPrimaryInterrupted.Broadcast();

    UE_LOG(LogTemp, Warning, TEXT("Primary attack interrupted!"));
}


void ACombatCharacter::PrimaryReleased(const FInputActionValue& Value)
{
    if (!PrimaryAvailable) return;

    ActionState = EActionState::ReleaseAttack;
    if (GetMesh() && GetMesh()->GetAnimInstance())
    {
        if (UAnimMontage* Montage = GetAttackMontage())
        {
            GetMesh()->GetAnimInstance()->Montage_Play(Montage);
        }
    }
}


void ACombatCharacter::SecondaryStarted(const FInputActionValue& Value)
{

    GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("Secondary started")));
}
void ACombatCharacter::SecondaryReleased(const FInputActionValue& Value)
{

    GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("Secondary released")));
}
void ACombatCharacter::OnRootMotionComplete()
{
    UE_LOG(LogTemp, Log, TEXT("Root motion complete!"));
}

void ACombatCharacter::OnRootMotionFailed()
{
    UE_LOG(LogTemp, Warning, TEXT("Root motion failed!"));
}

UMeleeTraceComponent* ACombatCharacter::GetMeleeTraceComponent()
{
    return MeleeTraceComponent;
}


void ACombatCharacter::CastStarted(const FInputActionValue& Value)
{                      

    ActionState = EActionState::StartCast;
}                      
void ACombatCharacter::CastReleased(const FInputActionValue& Value)
{
    ActionState = EActionState::ReleaseCast;
    if (GetMesh() && GetMesh()->GetAnimInstance()) {
        GetMesh()->GetAnimInstance()->Montage_Play(GetSpellMontage());
    }

}void ACombatCharacter::InteractStarted(const FInputActionValue& Value)
{
    if (CurrentInteractable && CurrentInteractable->Implements<UInteractable>())
    {
        IInteractable* Interactable = Cast<IInteractable>(CurrentInteractable);
        if (Interactable)
        {

            GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("try interact")));
            UE_LOG(LogTemp, Log, TEXT("trying interact"));
            Interactable->HandleInteraction(this);
        }
        else {
            GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("no interactable")));
            UE_LOG(LogTemp, Log, TEXT("no interactable"));
        }
    }
    else {

        GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("no interactable or doesnt implement uinteractable")));
    }
}
void ACombatCharacter::InteractReleased(const FInputActionValue& Value)
{
    UCharacterMovementComponent* Movement = GetCharacterMovement();
    if (!Movement) {

        UE_LOG(LogTemp, Log, TEXT("NO character movement"));
    }

    ActionState = EActionState::ReleaseCast;

  
    // Apply root motion forward during the cast
    FVector Forward = GetActorForwardVector();
    UAsyncRootMovement* RootMotionTask = UAsyncRootMovement::AsyncRootMovement(
        this,
        Movement,
        Forward,
        900.f,
        1.75f,
        false,
        nullptr,
        ERootMotionFinishVelocityMode::MaintainLastRootMotionVelocity,
        FVector::ZeroVector,
        0.0f,
        false
    );

    if (RootMotionTask)
    {
        UE_LOG(LogTemp, Log, TEXT("task creaetded"));
        RootMotionTask->OnComplete.AddDynamic(this, &ACombatCharacter::OnRootMotionComplete);
        RootMotionTask->OnFail.AddDynamic(this, &ACombatCharacter::OnRootMotionFailed);
    }
}

void ACombatCharacter::StartMeleeTrace()
{
    if (!MeleeTraceComponent || !PrimaryWeapon) {

        if (!MeleeTraceComponent) {

            UE_LOG(LogTemp, Log, TEXT("trace couldnt start: no meelcomponent"));
        }
        else {

            UE_LOG(LogTemp, Log, TEXT("trace couldnt start: no primary"));
        }
        return;
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("melee trace stated"));
    }


    FTraceSource TraceSource;
    TraceSource.Mesh = PrimaryWeapon; // 👈 Use PrimaryWeapon instead of GetMesh()

    TraceSource.Sockets.AddUnique(FName("Hit_01")); // Ensure your weapon mesh has these sockets
    TraceSource.Sockets.AddUnique(FName("Hit_02"));

    MeleeTraceComponent->StartTracing({ TraceSource });
}


void ACombatCharacter::StopMeleeTrace()
{
    if (MeleeTraceComponent)
    {
        MeleeTraceComponent->StopTracing();
    }
}

