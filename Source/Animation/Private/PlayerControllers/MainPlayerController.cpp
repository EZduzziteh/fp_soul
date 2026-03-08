// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/MainPlayerController.h"
// MyPlayerController.cpp
#include "ui/Widget_Hud.h"

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (MyWidgetClass) // This is a UPROPERTY pointing to your Widget Blueprint
    {
        HUDWidget = CreateWidget<UWidget_Hud>(this, MyWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            HUDWidget->SetText(TEXT("Hello, Unreal UI!"));
        }
    }
}



void AMainPlayerController::OpenInventoryWindow() {
    if (HUDWidget) {
        
        HUDWidget->ToggleInventoryWindow();
    }
}

void AMainPlayerController::OpenDialogueWindow(UTopicManagerComponent* topicManagerComponent) {
    if (HUDWidget) {

        HUDWidget->ToggleDialogueWindow(topicManagerComponent);
    }
}