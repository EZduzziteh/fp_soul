// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponInfo.h"
#include "EquipmentInfo.h"
#include "EquipmentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMATION_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEquipmentInfo Head;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEquipmentInfo Chest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEquipmentInfo Legs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEquipmentInfo Feet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponInfo Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponInfo Secondary;

		
};
