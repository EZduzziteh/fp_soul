// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget_Hud.h"
// MyUserWidget.cpp
#include "Components/TextBlock.h"

void UWidget_Hud::SetText(const FString& NewText)
{
    if (MyText)
    {
        MyText->SetText(FText::FromString(NewText));
    }
}
