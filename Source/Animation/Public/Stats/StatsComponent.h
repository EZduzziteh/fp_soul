// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMATION_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Health")
	int MaxHealth;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Stamina")
	int MaxStamina;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Mana")
	int MaxMana;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Health")
	int CurrentHealth;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Stamina")
	int CurrentStamina;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Mana")
	int CurrentMana;


	bool bRegenerateHealth = false;
	bool bRegenerateStamina = false;
	bool bRegenerateMana = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Health")
	float HealthRegenerationRate;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Stamina")
	float StaminaRegenerationRate;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "_Mana")
	float ManaRegenerationRate;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category ="_Regeneration")
	float RegenerationTickRate;

	FTimerHandle RegenerateTimer;






protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	void Regenerate();
		
};
