// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "_UI")
		TSubclassOf<class UWidget_Hud> MyWidgetClass;
	
		UPROPERTY()
		UWidget_Hud* HUDWidget;
		void BeginPlay();
};
