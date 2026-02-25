#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable/Interactable.h" 
#include "PickupItemInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Pickup.generated.h"

UCLASS()
class ANIMATION_API APickup : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	APickup();

protected:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPickupItemInfo> Items;
	
	virtual void HandleInteraction_Implementation(AActor* Interactor) override;

	virtual bool IsInteractionEnabled_Implementation() const override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* PickupSound;




private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* InteractionSphere;
};
