
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueTopic.h"
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
	// Called every frame
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FName> KnownTopics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bMetPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName NPCName;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue")
	FDialogueTopic GetTopicData(FName TopicName);
};