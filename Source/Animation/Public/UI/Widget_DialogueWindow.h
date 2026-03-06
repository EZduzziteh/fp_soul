// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialogue/TopicManagerComponent.h"
#include <Components/TextBlock.h>
#include "Widget_DialogueWindow.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATION_API UWidget_DialogueWindow : public UUserWidget
{
	GENERATED_BODY()
	public:

	void Setup(UTopicManagerComponent* topicManagerComponent);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueNPCNameText;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueLineText;


};
