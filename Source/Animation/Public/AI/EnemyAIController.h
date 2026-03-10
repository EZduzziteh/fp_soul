#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/EnemyCharacter.h"
#include "AI/Faction.h"
#include "EnemyAIController.generated.h"

UCLASS()
class ANIMATION_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AEnemyAIController();

protected:
    virtual void OnPossess(APawn* InPawn) override;

    UFUNCTION()
    void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, Category = "_Factions")
    EFaction faction;

    UPROPERTY(VisibleAnywhere, Category = "_Factions")
    TArray<EFaction> enemyFactions;

    UPROPERTY(VisibleAnywhere, Category = "_Factions")
    TArray<EFaction> friendlyFactions;

    UPROPERTY()
    UAISenseConfig_Sight* SightConfig;

    UPROPERTY()
    AEnemyCharacter* ControlledEnemy;
};
