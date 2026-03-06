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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Slots")
	FEquipmentInfo Head;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Slots")
	FEquipmentInfo Chest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Slots")
	FEquipmentInfo Legs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Slots")
	FEquipmentInfo Feet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Slots")
	FWeaponInfo Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Slots")
	FWeaponInfo Secondary;

	UFUNCTION(BlueprintCallable)
	void Equip(FEquipmentInfo equipmentInfo);

		
};
