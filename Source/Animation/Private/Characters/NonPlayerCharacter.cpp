// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NonPlayerCharacter.h"
#include "PlayerControllers/MainPlayerController.h"
#include <Utilities/EZLog.h>

// Sets default values
ANonPlayerCharacter::ANonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // Create the interaction sphere
    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));

    InteractionSphere->SetupAttachment(RootComponent);
    InteractionSphere->InitSphereRadius(100.f);



    // Collision settings - allow traces but no blocking
    InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
    InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionSphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // For raycasts



     TopicManagerComponent = CreateDefaultSubobject<UTopicManagerComponent>(TEXT("InventoryComponent"));

}

// Called when the game starts or when spawned
void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANonPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANonPlayerCharacter::HandleInteraction_Implementation(AActor* Interactor)
{
    if (!IInteractable::Execute_IsInteractionEnabled(this)) {
        DEBUG(TEXT("Interact not enabled"));
        return;
    }
   

    UE_LOG(LogTemp, Warning, TEXT("NPC interacted with by %s"), *Interactor->GetName());


    ACharacter* character = Cast<ACharacter>(Interactor);
    if (character) {
        AController* controller = character->GetController();
        if (controller) {
            AMainPlayerController* mainPlayerController = Cast<AMainPlayerController>(controller);
            if (mainPlayerController) {
                mainPlayerController->OpenDialogueWindow(TopicManagerComponent);
            }
        }
    }


    //#TODO Open dialogue Window
}

bool ANonPlayerCharacter::IsInteractionEnabled_Implementation() const
{
    return bInteractionEnabled;
}





