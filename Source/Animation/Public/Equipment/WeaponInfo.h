#pragma once

#include "CoreMinimal.h"
#include "WeaponClass.h"
#include "WeaponAction.h"
#include "WeaponInfo.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponClass WeaponType = EWeaponClass::Sword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Actions")
	FWeaponAction UpAction; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Actions")
	FWeaponAction DownAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Actions")
	FWeaponAction LeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Actions")
	FWeaponAction RightAction;

};
