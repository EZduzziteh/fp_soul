// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget_Hud.h"
#include "Components/TextBlock.h"

void UWidget_Hud::SetText(const FString& NewText)
{
    if (InteractionMessageText)
    {
        InteractionMessageText->SetText(FText::FromString(NewText));
    }
}


void UWidget_Hud::ToggleInventoryWindow()
{
    if (InventoryWindowWidget)
    {
        switch (InventoryWindowWidget->GetVisibility()) {
        case ESlateVisibility::Visible:
            InventoryWindowWidget->SetVisibility(ESlateVisibility::Hidden);
            break;
        case ESlateVisibility::Hidden:
            InventoryWindowWidget->SetVisibility(ESlateVisibility::Visible);
            break;
        }
    }
}


void UWidget_Hud::ToggleDialogueWindow(UTopicManagerComponent* topicManagerComponent) {
    if (DialogueWindowWidget)
    {
        switch (DialogueWindowWidget->GetVisibility()) {
        case ESlateVisibility::Visible:
            DialogueWindowWidget->SetVisibility(ESlateVisibility::Hidden);
            break;
        case ESlateVisibility::Hidden:
            DialogueWindowWidget->SetVisibility(ESlateVisibility::Visible);
            DialogueWindowWidget->Setup(topicManagerComponent);
            break;
        }
    }
}
