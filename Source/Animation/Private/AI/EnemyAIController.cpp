#include "AI/EnemyAIController.h"
#include "Characters/EnemyCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Utilities/EZLog.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyAIController::AEnemyAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    if (SightConfig)
    {
        SightConfig->SightRadius = 1500.f;
        SightConfig->LoseSightRadius = 1800.f;
        SightConfig->PeripheralVisionAngleDegrees = 75.f;
        SightConfig->SetMaxAge(5.f);

        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

        AIPerceptionComponent->ConfigureSense(*SightConfig);
        AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
        AIPerceptionComponent->bAutoActivate = true; // ensures it's active
        SetPerceptionComponent(*AIPerceptionComponent); // critical

        DEBUG("AIController: Sight Initialized");
    }
    else {

        DEBUG("AIController: No Sight Config!");
    }


    DEBUG("AIController: Initialized AI Controller");
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ControlledEnemy = Cast<AEnemyCharacter>(InPawn);

    if (AIPerceptionComponent)
    {
        AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(
            this,
            &AEnemyAIController::OnPerceptionUpdated
        );


        DEBUG("AIController: Perception Initialized");
    }
}

void AEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (!ControlledEnemy) return;

    if (Stimulus.WasSuccessfullySensed())
    {

        ControlledEnemy->CombatTarget = Actor;
        ControlledEnemy->AIState = EEnemyAIState::Combat;

        DEBUG("AIController: Spotted player");
    }
    else if (Actor == ControlledEnemy->CombatTarget)
    {
        ControlledEnemy->CombatTarget = nullptr;
        ControlledEnemy->AIState = EEnemyAIState::Patrol;

        DEBUG("AIController: Lost player");
    }
    else {

        DEBUG("AIController: Unhandled Case");
    }
}
