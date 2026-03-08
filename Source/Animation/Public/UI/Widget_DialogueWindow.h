// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialogue/TopicManagerComponent.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include "UI/Widget_DialogueEntry.h"

#include "Widget_DialogueWindow.generated.h"
/**
 * 
 */
UCLASS()
class ANIMATION_API UWidget_DialogueWindow : public UUserWidget
{
	GENERATED_BODY()
	public:


		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UWidget_DialogueEntry> DialogueEntryClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTopicManagerComponent* TopicManagerComponentReference;

		void Setup(UTopicManagerComponent* topicManagerComponent);

		UPROPERTY(meta = (BindWidget))
		UTextBlock* NPCNameText;


		UPROPERTY(meta=(BindWidget))
		UVerticalBox* DialogueEntries;


		UPROPERTY(meta = (BindWidget))
		UVerticalBox* Topics;

		UFUNCTION(BlueprintCallable)
		void SetNPCName(FText text);


		UFUNCTION(BlueprintCallable)
		void AddDialogueEntry(UWidget_DialogueEntry* DialogueEntry);


		UFUNCTION(BlueprintCallable)
		void ClearDialogueEntries();




};
