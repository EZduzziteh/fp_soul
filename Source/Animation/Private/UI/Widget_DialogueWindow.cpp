// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget_DialogueWindow.h"
#include "Kismet/GameplayStatics.h"

void UWidget_DialogueWindow::Setup(UTopicManagerComponent* topicManagerComponent)
{
	TopicManagerComponentReference = topicManagerComponent;
	SetNPCName(FText::FromString(topicManagerComponent->NPCName.ToString()));

	
	FDialogueTopic data = topicManagerComponent->GetTopicData("Greet");


	//Play Line Audo

	
	
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		data.Line.Audio,
		topicManagerComponent->GetOwner()->GetActorLocation()
		);


	UWidget_DialogueEntry* NewDialogueEntry =
		CreateWidget<UWidget_DialogueEntry>(GetWorld(), DialogueEntryClass);

	NewDialogueEntry->Setup(FText::FromString(topicManagerComponent->NPCName.ToString()), data.Line.Text);



	AddDialogueEntry(NewDialogueEntry);
	
}

void UWidget_DialogueWindow::SetNPCName(FText text)
{
	NPCNameText->SetText(text);
}

void UWidget_DialogueWindow::AddDialogueEntry(UWidget_DialogueEntry* DialogueEntry)
{

	DialogueEntries->AddChild(DialogueEntry);
}

void UWidget_DialogueWindow::ClearDialogueEntries()
{
	DialogueEntries->ClearChildren();
}
