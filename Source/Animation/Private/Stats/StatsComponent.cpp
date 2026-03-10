// Fill out your copyright notice in the Description page of Project Settings.


#include "Stats/StatsComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		RegenerateTimer,                 // Handle
		this,                          // Object
		&UStatsComponent::Regenerate,    // Function to call
		RegenerationTickRate,                          // Time delay (seconds)
		true                           // Loop? true = repeat
	);

}


void UStatsComponent::Regenerate()
{
	if (bRegenerateHealth) {
		if (CurrentHealth < MaxHealth) {
			CurrentHealth += HealthRegenerationRate;
		}
	}
	if (bRegenerateMana) {
		if (CurrentMana < MaxMana) {
			CurrentMana += ManaRegenerationRate;
		}
	}
	if (bRegenerateStamina) {
		if (CurrentStamina < MaxStamina) {
			CurrentStamina += StaminaRegenerationRate;
			
		}
	}


	if (CurrentHealth > MaxHealth) {
		CurrentHealth = MaxHealth;
	}
	if (CurrentMana > MaxMana) {
		CurrentMana = MaxMana;
	}
	if (CurrentStamina > MaxStamina) {
		CurrentStamina = MaxStamina;
	}
	

}



