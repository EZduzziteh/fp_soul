#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Magic/SpellbookComponent.h" // include your component header
#include "Stats/StatsComponent.h"
#include "AsyncRootMovement.h"
#include "Combat/Damageable.h"
#include "Equipment/EquipmentComponent.h"
#include "Interactable/Interactable.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Combat/MeleeTraceComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Combat/Damager.h"
#include "Combat/ActionState.h"
#include "Combat/MouseDirection.h"
#include "Combat/MoveDirection.h"
#include "CombatCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;

// Declare a dynamic multicast delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPrimaryInterrupted);


UCLASS()
class ANIMATION_API ACombatCharacter : public ACharacter, public IDamageable, public IDamager
{
    GENERATED_BODY()

public:

    float TraceDistance = 300.f;
    float TraceRadius = 30.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
    UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;



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

 


  

public:    
    
    
    UPROPERTY(BlueprintReadOnly, Category = "_Mouse Movement")
    EMouseDirection MouseDirection;
    UPROPERTY(BlueprintReadOnly, Category = "_Combat")
      EMouseDirection AttackDirection;
    UPROPERTY(BlueprintReadOnly, Category = "_Mouse Movement")
    EMoveDirection LastMoveDirection;
    UPROPERTY()
	AActor* CurrentInteractable;

    UFUNCTION(BlueprintCallable, Category = "_Melee Tracing")
    void StopMeleeTrace();
    UFUNCTION(BlueprintCallable, Category = "_Melee Tracing")
    void StartMeleeTrace();



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


};
