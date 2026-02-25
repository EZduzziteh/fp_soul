#include "Inventory/Pickup.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Utilities/EZLog.h"
#include "Inventory/InventoryComponent.h"
// Sets default values
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the interaction sphere
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->InitSphereRadius(100.f);

	// Collision settings - allow traces but no blocking
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // For raycasts
}


void APickup::HandleInteraction_Implementation(AActor* Interactor)
{
    if (!IInteractable::Execute_IsInteractionEnabled(this)) {
        DEBUG(TEXT("Interact not enabled"));
        return;
    }

    GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("interacted with")));
    UE_LOG(LogTemp, Warning, TEXT("Pickup interacted with by %s"), *Interactor->GetName());

    if (UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>())
    {
        for (const FPickupItemInfo& Item : Items)
        {
            Inventory->AddItem(Item.ItemID, Item.Quantity);
            UE_LOG(LogTemp, Log, TEXT("Added %d x %s to inventory"), Item.Quantity, *Item.ItemID);
        }

        // ?? Play pickup sound
        if (PickupSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
        }

        Destroy();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Interactor has no inventory component"));
    }
}

bool APickup::IsInteractionEnabled_Implementation() const
{
    return true;
}



