#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "CombatCharacter.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

// =========================
// CONSTRUCTOR
// =========================

AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // ?? IMPORTANT — use custom AI controller
    AIControllerClass = AEnemyAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // --- Components ---
    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
    SpellbookComponent = CreateDefaultSubobject<USpellbookComponent>(TEXT("SpellbookComponent"));
    StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
    EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
    MeleeTraceComponent = CreateDefaultSubobject<UMeleeTraceComponent>(TEXT("MeleeTraceComponent"));

    // --- Weapons ---
    PrimaryWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PrimaryWeapon"));
    PrimaryWeapon->SetupAttachment(GetMesh(), FName("Item_R"));
    PrimaryWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SecondaryWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SecondaryWeapon"));
    SecondaryWeapon->SetupAttachment(GetMesh(), FName("Item_L"));
    SecondaryWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// =========================
// BEGIN PLAY
// =========================

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    AIController = Cast<AAIController>(GetController());
}

// =========================
// TICK
// =========================

void AEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (AIState)
    {
    case EEnemyAIState::Waiting: HandleWaiting(); break;
    case EEnemyAIState::Wander: HandleWander(); break;
    case EEnemyAIState::Patrol: HandlePatrol(); break;
    case EEnemyAIState::Combat: HandleCombat(); break;
    }
}

// =========================
// STATE HANDLERS
// =========================

void AEnemyCharacter::HandleWaiting() {}

void AEnemyCharacter::HandleWander()
{
    FVector Point = GetRandomWanderPoint();
    MoveToLocation(Point);
    AIState = EEnemyAIState::Waiting;
}

void AEnemyCharacter::HandlePatrol()
{
    if (PatrolPoints.Num() == 0 || !AIController) return;

    FVector Target = PatrolPoints[CurrentPatrolIndex]->GetActorLocation();
    MoveToLocation(Target);

    if (FVector::Dist(GetActorLocation(), Target) < 100.f)
    {
        ChooseNextPatrolPoint();
    }
}

void AEnemyCharacter::HandleCombat()
{
    if (!CombatTarget || !AIController) return;
    CombatTick();
}

// =========================
// COMBAT LOGIC
// =========================

void AEnemyCharacter::CombatTick()
{
    if (!CombatTarget || !AIController) return;

    float Distance = FVector::Dist(GetActorLocation(), CombatTarget->GetActorLocation());
    FVector DirectionToPlayer = (CombatTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    FVector DirectionAway = -DirectionToPlayer;

    // --- BLOCK ---
    if (!bIsBlocking)
    {
        if (FMath::FRand() < BlockChance)
        {
            StartBlocking();
            return;
        }
    }

    // --- DODGE ---
    AttemptDodge();

    // --- MOVEMENT ---
    if (Distance > DesiredCombatRange)
    {
        MoveToLocation(GetActorLocation() + DirectionToPlayer * FMath::Clamp(Distance - DesiredCombatRange, 100.f, 600.f));
        return;
    }
    else if (Distance < DesiredCombatRange * 0.7f)
    {
        MoveToLocation(GetActorLocation() + DirectionAway * 300.f);
        return;
    }

    // --- ATTACK OR STRAFE ---
    float AttackChance = 0.5f + Aggression * 0.5f;

    if (FMath::FRand() < AttackChance)
    {
        if (UAnimMontage* Montage = GetAttackMontage())
        {
            PlayAttackMontage(Montage);
        }
    }
    else
    {
        FVector StrafeDir = FVector::CrossProduct(DirectionToPlayer, FVector::UpVector);
        if (FMath::FRand() < 0.5f)
            MoveToLocation(GetActorLocation() + StrafeDir * 200.f);
        else
            MoveToLocation(GetActorLocation() - StrafeDir * 200.f);
    }
}

// =========================
// DODGE
// =========================

void AEnemyCharacter::AttemptDodge()
{
    if (!CombatTarget) return;

    ACombatCharacter* Player = Cast<ACombatCharacter>(CombatTarget);
    if (!Player) return;

    if (Player->GetActionState() == EActionState::StartAttack)
    {
        if (FMath::FRand() < DodgeChance)
        {
            if (DodgeMontage) PlayAttackMontage(DodgeMontage);

            FVector DodgeDir =
                FVector::CrossProduct(
                    (GetActorLocation() - Player->GetActorLocation()).GetSafeNormal(),
                    FVector::UpVector);

            MoveToLocation(GetActorLocation() + DodgeDir * 400.f);
        }
    }
}

// =========================
// BLOCK
// =========================

void AEnemyCharacter::StartBlocking()
{
    if (!BlockMontage || bIsBlocking) return;

    bIsBlocking = true;

    if (GetMesh() && GetMesh()->GetAnimInstance())
    {
        GetMesh()->GetAnimInstance()->Montage_Play(BlockMontage);
    }

    GetWorld()->GetTimerManager().SetTimer(
        BlockTimerHandle,
        this,
        &AEnemyCharacter::StopBlocking,
        BlockDuration,
        false);
}

void AEnemyCharacter::StopBlocking()
{
    bIsBlocking = false;
}

// =========================
// MOVEMENT HELPERS
// =========================

void AEnemyCharacter::MoveToLocation(const FVector& Location)
{
    if (AIController)
    {
        AIController->MoveToLocation(Location);
    }
}

void AEnemyCharacter::ChooseNextPatrolPoint()
{
    CurrentPatrolIndex = (CurrentPatrolIndex + 1) % PatrolPoints.Num();
}

FVector AEnemyCharacter::GetRandomWanderPoint()
{
    FVector Origin = GetActorLocation();
    FNavLocation NavPoint;

    if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
    {
        if (NavSystem->GetRandomReachablePointInRadius(Origin, WanderRadius, NavPoint))
        {
            return NavPoint.Location;
        }
    }

    return Origin;
}

// =========================
// ATTACK INTERFACE
// =========================

UAnimMontage* AEnemyCharacter::GetAttackMontage_Implementation()
{
    return AttackMontage;
}

void AEnemyCharacter::PlayAttackMontage_Implementation(UAnimMontage* Montage)
{
    if (Montage && GetMesh() && GetMesh()->GetAnimInstance())
    {
        GetMesh()->GetAnimInstance()->Montage_Play(Montage);
    }
}
