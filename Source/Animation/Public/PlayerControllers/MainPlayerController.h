// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget_Hud.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATION_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	public: 
	
		virtual void BeginPlay() override;
		UFUNCTION(BlueprintCallable)
		void OpenInventoryWindow();

		UFUNCTION(BlueprintCallable)
		void OpenDialogueWindow(UTopicManagerComponent* topicManagerComponent);

		

		UPROPERTY(BlueprintReadOnly, Category = "_UI")
		UWidget_Hud* HUDWidget;

	protected:
		

		UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_UI")
		TSubclassOf<class UWidget_Hud> MyWidgetClass;
};
