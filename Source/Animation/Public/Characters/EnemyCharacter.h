#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI/EnemyAIState.h"
#include "EnemyCharacter.generated.h"

class UInventoryComponent;
class USpellbookComponent;
class UStatsComponent;
class UEquipmentComponent;
class UMeleeTraceComponent;
class AEnemyAIController;
class AAIController;
class UAnimMontage;

UCLASS()
class ANIMATION_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // === AI ===
    void HandleWaiting();
    void HandleWander();
    void HandlePatrol();
    void HandleCombat();
    void CombatTick();

    void MoveToLocation(const FVector& Location);
    void ChooseNextPatrolPoint();
    FVector GetRandomWanderPoint();

    // === Combat helpers ===
    void AttemptDodge();
    void StartBlocking();
    void StopBlocking();

public:

    // =========================
    // COMPONENTS
    // =========================

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UInventoryComponent* InventoryComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpellbookComponent* SpellbookComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStatsComponent* StatsComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UEquipmentComponent* EquipmentComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UMeleeTraceComponent* MeleeTraceComponent;

    // =========================
    // WEAPONS
    // =========================

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
    USkeletalMeshComponent* PrimaryWeapon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
    USkeletalMeshComponent* SecondaryWeapon;

    // =========================
    // AI STATE
    // =========================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    EEnemyAIState AIState = EEnemyAIState::Waiting;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Wander")
    float WanderRadius = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Patrol")
    TArray<AActor*> PatrolPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
    float DesiredCombatRange = 400.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Combat")
    AActor* CombatTarget = nullptr;

    // =========================
    // COMBAT TUNING
    // =========================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Aggression = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float DodgeChance = 0.25f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
    UAnimMontage* DodgeMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float BlockChance = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
    float BlockDuration = 1.5f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Combat")
    bool bIsBlocking = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
    UAnimMontage* BlockMontage;

    // =========================
    // ATTACK INTERFACE
    // =========================

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    UAnimMontage* GetAttackMontage();
    virtual UAnimMontage* GetAttackMontage_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    void PlayAttackMontage(UAnimMontage* Montage);
    virtual void PlayAttackMontage_Implementation(UAnimMontage* Montage);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    UAnimMontage* AttackMontage;

private:
    int32 CurrentPatrolIndex = 0;
    AAIController* AIController = nullptr;

    FTimerHandle BlockTimerHandle;
};
