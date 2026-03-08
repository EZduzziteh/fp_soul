// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget_DialogueEntry.h"

void UWidget_DialogueEntry::Setup(FText speakerName, FText speakerText)
{

	SpeakerNameText->SetText(speakerName);
	EntryText->SetText(speakerText);

}
