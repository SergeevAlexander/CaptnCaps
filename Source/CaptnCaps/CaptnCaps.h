// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

// after creating and setting a new Trace Channel in projects settings
#define ECC_Weapon ECC_GameTraceChannel1

#include "Engine.h"
#include "CaptnCaps.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCaptnCaps, Log, All);

UENUM(BlueprintType)
enum class EStencilColor : uint8
{
	SC_Green = 250 UMETA(DisplayName = "Green"),
	SC_Blue = 251 UMETA(DisplayName = "Blue"),
	SC_Red = 252 UMETA(DisplayName = "Red"),
	SC_Orange = 253 UMETA(DisplayName = "Orange"),
};


UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	AT_Bullets UMETA(DisplayName = "Bullets"),
	SC_Rockets UMETA(DisplayName = "Rockets"),
	SC_Lasers  UMETA(DisplayName = "Lasers"),
};


USTRUCT(BlueprintType)
struct FPlayerInventory
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	class AWeaponBase* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	class AAssaultRifleBase* AssaultRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	class ALaserRifleBase* LaserRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	class ARocketLauncherBase* RocketLauncher;
};


USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	TSubclassOf<class AWaveEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	int32 MaxEnemiesAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float Probability;
	
};


USTRUCT(BlueprintType)
struct FWaveInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	int32 TotalNumberOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	TArray<FSpawnInfo> SpawnInfo;

};


