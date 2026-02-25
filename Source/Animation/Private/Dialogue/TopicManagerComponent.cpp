// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/TopicManagerComponent.h"
#include "Dialogue/NPCDialogueRegistry.h"
#include "Dialogue/DialogueTopic.h"
#include "Utilities/EZLog.h"
#include <Dialogue/DialogueNPC.h>

// Sets default values for this component's properties
UTopicManagerComponent::UTopicManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTopicManagerComponent::BeginPlay()
{
	Super::BeginPlay();

    LoadNPCTopics();
	
}





void UTopicManagerComponent::LoadNPCTopics()
{
    DEBUG(TEXT("Loading NPC Topics"));
    static const FString Context(TEXT("NPC Registry"));

    if (!NPCRegistryTable)
    {
        UE_LOG(LogTemp, Error, TEXT("NPCRegistryTable is NULL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("NPCName = %s"), *NPCName.ToString());

    FNPCDialogueRegistryRow* RegistryRow =
        NPCRegistryTable->FindRow<FNPCDialogueRegistryRow>(NPCName, Context);

    if (!RegistryRow)
    {
        UE_LOG(LogTemp, Error, TEXT("No registry row found for NPC: %s"), *NPCName.ToString());
        return;
    }

    NPCTopicDataTable = RegistryRow->NPCTopicTable;
}

FDialogueTopic UTopicManagerComponent::GetTopicData(FName TopicName)
{
    static const FString Context(TEXT("Topic Lookup"));

    if (NPCTopicDataTable)
    {
        return FDialogueTopic();
    }

    FDialogueTopic* TopicRow = NPCTopicDataTable->FindRow<FDialogueTopic>(TopicName, Context);

    if (!TopicRow)
    {
        return FDialogueTopic();
    }

    return *TopicRow;
}



