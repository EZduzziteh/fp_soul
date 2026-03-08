// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "Widget_DialogueEntry.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATION_API UWidget_DialogueEntry : public UUserWidget
{
	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable)
	void Setup(FText speakerName, FText speakerText);


	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpeakerNameText;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* EntryText;
	
};
