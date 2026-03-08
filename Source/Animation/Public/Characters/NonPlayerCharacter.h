// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable/Interactable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Dialogue/TopicManagerComponent.h"
#include "NonPlayerCharacter.generated.h"

UCLASS()
class ANIMATION_API ANonPlayerCharacter : public ACharacter, public IInteractable
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Inherited via IInteractable
	//void HandleInteraction(AActor* Interactor) override;

	virtual void HandleInteraction_Implementation(AActor* Interactor)override;


	virtual bool IsInteractionEnabled_Implementation() const override;



};
