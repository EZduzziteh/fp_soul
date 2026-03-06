#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Magic/SpellbookComponent.h" // include your component header
#include "Stats/StatsComponent.h"
#include "AsyncRootMovement.h"
#include "Equipment/EquipmentComponent.h"
#include "Interactable/Interactable.h"
#include "Combat/MeleeTraceComponent.h"
#include "Inventory/InventoryComponent.h"
#include "CombatCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UENUM(BlueprintType)
enum class EMouseDirection : uint8
{
    None        UMETA(DisplayName = "None"),
    Up          UMETA(DisplayName = "Up"),
    Down        UMETA(DisplayName = "Down"),
    Left        UMETA(DisplayName = "Left"),
    Right       UMETA(DisplayName = "Right"),
    UpRight     UMETA(DisplayName = "Up Right"),
    UpLeft      UMETA(DisplayName = "Up Left"),
    DownRight   UMETA(DisplayName = "Down Right"),
    DownLeft    UMETA(DisplayName = "Down Left")
}; 

UENUM(BlueprintType)
enum class EMoveDirection : uint8
{
    None        UMETA(DisplayName = "None"),
    Up          UMETA(DisplayName = "Up"),
    Down        UMETA(DisplayName = "Down"),
    Left        UMETA(DisplayName = "Left"),
    Right       UMETA(DisplayName = "Right"),
    UpRight     UMETA(DisplayName = "Up Right"),
    UpLeft      UMETA(DisplayName = "Up Left"),
    DownRight   UMETA(DisplayName = "Down Right"),
    DownLeft    UMETA(DisplayName = "Down Left")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
    None            UMETA(DisplayName = "None"),
    StartAttack     UMETA(DisplayName = "StartAttack"),
    HoldAttack      UMETA(DisplayName = "HoldAttack"),
    ReleaseAttack   UMETA(DisplayName = "ReleaseAttack"),
    ReleaseCast     UMETA(DisplayName = "ReleaseCast"),
    StartCast       UMETA(DisplayName = "StartCast")
};

// Declare a dynamic multicast delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPrimaryInterrupted);


UCLASS()
class ANIMATION_API ACombatCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Camera")
    class UCameraComponent* CameraComponent;

    ACombatCharacter();
    EActionState GetActionState() const { return ActionState; }
    UFUNCTION()
    void OnRootMotionComplete();

    UFUNCTION()
    void OnRootMotionFailed();

    UFUNCTION()
    UMeleeTraceComponent* GetMeleeTraceComponent();
    UPROPERTY(BlueprintReadWrite, Category = "_Action")
    EActionState ActionState;
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Camera")
    FVector LocalOffset = FVector(-15.f, 0.f, 10.f); 
    // Weapon mesh components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    USkeletalMeshComponent* PrimaryWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    USkeletalMeshComponent* SecondaryWeapon;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UInventoryComponent* InventoryComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USpellbookComponent* SpellbookComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStatsComponent* StatsComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UEquipmentComponent* EquipmentComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UMeleeTraceComponent* MeleeTraceComponent;



    UPROPERTY(BlueprintReadOnly, Category = "_Mouse Movement")
    EMouseDirection MouseDirection;
    UPROPERTY(BlueprintReadOnly, Category = "_Combat")
    EMouseDirection AttackDirection;


    UPROPERTY(BlueprintReadOnly, Category = "_Mouse Movement")
    EMoveDirection LastMoveDirection;


    // Input handlers
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void DetectMovementDirection(FVector2D Input);
    void PrimaryStarted(const FInputActionValue& Value);
    void PrimaryReleased(const FInputActionValue& Value);
    void SecondaryStarted(const FInputActionValue& Value);
    void SecondaryReleased(const FInputActionValue& Value);
    void CastStarted(const FInputActionValue& Value);
    void CastReleased(const FInputActionValue& Value);
    void JumpStarted(const FInputActionValue& Value);
    void InteractStarted(const FInputActionValue& Value);
    void InteractReleased(const FInputActionValue& Value);
    void OpenInventoryStarted(const FInputActionValue& Value);

    // Mouse movement detection
    void DetectMouseDirection(float DeltaX, float DeltaY);

public:

    UPROPERTY()
	AActor* CurrentInteractable;

    UFUNCTION(BlueprintCallable, Category = "_Melee Tracing")
    void StopMeleeTrace();
    UFUNCTION(BlueprintCallable, Category = "_Melee Tracing")
    void StartMeleeTrace();

    /** Returns the last detected mouse direction (usable in AnimBP, etc.) */
    UFUNCTION(BlueprintCallable, Category = "_Mouse Movement")
    EMouseDirection GetLastMouseDirection() const;

    UFUNCTION(BlueprintCallable, Category = "_Mouse Movement")
    EMoveDirection GetLastMoveDirection() const;

    // Tracks the current pitch from controller input
    UPROPERTY(BlueprintReadOnly, Category = "_Aiming")
    float LookPitch = 0.f;

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "_Combat")
    UAnimMontage* GetAttackMontage(); 
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "_Magic")
    UAnimMontage* GetSpellMontage();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void SetInteractionMessage(const FString& Message);

    // Required to define it in C++ instead of Blueprint
    virtual void SetInteractionMessage_Implementation(const FString& Message);




    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Combat")
    bool PrimaryAvailable = true;

    // This is the event you can bind to in Blueprints
    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnPrimaryInterrupted OnPrimaryInterrupted;

    // Interrupt function (BlueprintNativeEvent so it can be overridden)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    void InterruptPrimaryAttack();
    virtual void InterruptPrimaryAttack_Implementation();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Settings")
    float HorizontalSensitivity = 0.5f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Settings")
    float VerticalSensitivity = 0.5f;



    // Input mapping context for enhanced input system
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputMappingContext* DefaultMappingContext;

    // Input actions
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputAction* PrimaryAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputAction* SecondaryAction; 
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputAction* CastAction; 
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputAction* InteractAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputAction* JumpAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_Input")
    UInputAction* OpenInventoryAction;



    // Mouse movement tracking
    UPROPERTY(BlueprintReadOnly, Category = "_Mouse Movement")
    EMouseDirection LastMouseDirection = EMouseDirection::None;

    // Threshold for mouse movement to detect direction
    UPROPERTY(EditAnywhere, Category = "_Mouse Movement")
    float MouseMovementThreshold = 1.0f;

};
