// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget_Hud.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Characters/CombatCharacter.h"
#include "Combat/MouseDirection.h"
#include "Combat/MoveDirection.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainPlayerController.generated.h"


class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class ANIMATION_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	

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
		ACombatCharacter* ControlledCombatCharacter;
		AMainPlayerController();  // Default constructor
		/** Returns the last detected mouse direction (usable in AnimBP, etc.) */
		UFUNCTION(BlueprintCallable, Category = "_Mouse Movement")
		EMouseDirection GetLastMouseDirection() const;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Camera")
		FVector LocalOffset = FVector(-15.f, 0.f, 10.f);
		virtual void SetupInputComponent() override;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Camera")
		class UCameraComponent* CameraComponent;
	
		virtual void Tick(float DeltaTime) override;

		virtual void BeginPlay() override;
		UFUNCTION(BlueprintCallable)
		void OpenInventoryWindow();

		UFUNCTION(BlueprintCallable)
		void OpenDialogueWindow(UTopicManagerComponent* topicManagerComponent);

		

		UPROPERTY(BlueprintReadOnly, Category = "_UI")
		UWidget_Hud* HUDWidget;

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


		UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_UI")
		TSubclassOf<class UWidget_Hud> MyWidgetClass;


		// Mouse movement tracking
		UPROPERTY(BlueprintReadOnly, Category = "_Mouse Movement")
		EMouseDirection LastMouseDirection = EMouseDirection::None;

		// Threshold for mouse movement to detect direction
		UPROPERTY(EditAnywhere, Category = "_Mouse Movement")
		float MouseMovementThreshold = 1.0f;
};
