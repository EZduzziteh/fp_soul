#include "Characters/CombatCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AsyncRootMovement.h"
#include "PlayerControllers//MainPlayerController.h"
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

    AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
   
    /*Core Components*/
    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
    SpellbookComponent = CreateDefaultSubobject<USpellbookComponent>(TEXT("SpellbookComponent"));
    StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
    EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent")); 
    MeleeTraceComponent = CreateDefaultSubobject<UMeleeTraceComponent>(TEXT("MeleeTraceComponent"));



    /*Weapon Meshes - probably will need to move this to be handled in equipment component on equip?*/
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
   
}

void ACombatCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //#NOTE: will have to change this when its player-run
    //FVector Start = CameraComponent->GetComponentLocation();
    //FVector End = Start + (CameraComponent->GetForwardVector() * TraceDistance);

    FVector Start = GetActorLocation();
    FVector End = Start + GetActorForwardVector() * TraceDistance;

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
            if (IInteractable::Execute_IsInteractionEnabled(HitActor))
            {
                CurrentInteractable = HitActor; // store the actor
                if (IsValid(this) && HasAuthority() && CurrentInteractable)
                {


                    SetInteractionMessage(TEXT("Press E to Interact with ") + CurrentInteractable->GetName());
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
    else
    {
        if (IsValid(this) && HasAuthority())
        {
            SetInteractionMessage(TEXT(""));
        }
        CurrentInteractable = nullptr;
    }
}




// Get last mouse direction
EMoveDirection ACombatCharacter::GetLastMoveDirection() const
{
    return LastMoveDirection;
}

void ACombatCharacter::SetInteractionMessage_Implementation(const FString& Message)
{
   
        AMainPlayerController* mainPlayerController = Cast<AMainPlayerController>(GetController());

        if (mainPlayerController) {
            mainPlayerController->HUDWidget->SetText(Message);
        }
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

