
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "DialogueTopic.h"
#include "Components/SphereComponent.h"
#include "Interactable/Interactable.h"
#include "TopicManagerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ANIMATION_API UTopicManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTopicManagerComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDataTable* NPCRegistryTable;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FName> KnownTopics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bMetPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName NPCName;

	void LoadNPCTopics();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")

	FDialogueTopic GetTopicData(FName TopicName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* NPCTopicDataTable;


};