#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI/EnemyAIState.h"
#include "Combat/Damager.h"
#include "Combat/Damageable.h"
#include "Characters/CombatCharacter.h"
#include "EnemyCharacter.generated.h"

class UInventoryComponent;
class USpellbookComponent;
class UStatsComponent;
class UEquipmentComponent;
class UMeleeTraceComponent;
class AEnemyAIController;
class AAIController;
class UAnimMontage;




/*This is meant for enemies that are not interactable*/

UCLASS()
class ANIMATION_API AEnemyCharacter : public ACombatCharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

};
