// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable/Interactable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Dialogue/TopicManagerComponent.h"
#include "Combat/Damager.h"
#include "Combat/Damageable.h"
#include "Characters/CombatCharacter.h"
#include "NonPlayerCharacter.generated.h"


/*This is meant for characters that are interactable, and potentially cna be enemies.*/

UCLASS()
class ANIMATION_API ANonPlayerCharacter : public ACombatCharacter, public IInteractable
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	UTopicManagerComponent* TopicManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInteractionEnabled = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* InteractionSphere;

	// Sets default values for this character's properties
	ANonPlayerCharacter();

public:	
	// Inherited via IInteractable
	virtual void HandleInteraction_Implementation(AActor* Interactor)override;

	virtual bool IsInteractionEnabled_Implementation() const override;

};
