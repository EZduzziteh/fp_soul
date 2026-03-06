// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget_Inventory_Window.h"
#include "UI/Widget_ShopWindow.h"
#include "UI/Widget_StatsWindow.h"
#include "UI/Widget_DialogueWindow.h"
#include "Dialogue/TopicManagerComponent.h"
#include <Components/TextBlock.h>
#include "Widget_Hud.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATION_API UWidget_Hud : public UUserWidget
{
	GENERATED_BODY()

public:
    

    void SetText(const FString& NewText);
    void ToggleInventoryWindow();
    void ToggleDialogueWindow(UTopicManagerComponent* topicManagerComponent);
    void ToggleShopWindow();
    void ToggleStatsWindow();




    UPROPERTY(meta = (BindWidget))
    UTextBlock* InteractionMessageText;

    UPROPERTY(meta = (BindWidget))
    UWidget_Inventory_Window* InventoryWindowWidget;

    UPROPERTY(meta = (BindWidget))
    UWidget_DialogueWindow* DialogueWindowWidget;

    UPROPERTY(meta = (BindWidget))
    UWidget_ShopWindow* ShopWindowWidget;

    UPROPERTY(meta = (BindWidget))
    UWidget_StatsWindow* StatsWindowWidget;
};

