// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

class AInteractableActor;
struct FSaveGameStruct;

UCLASS()
class CAPTNCAPS_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void RotateCharacterTowardsMouseCursor();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	AInteractableActor* FindFocusedActor();

	void OnDeath();

	void Heal(float Amount);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void HUDUpdateHP();

	void AddAmmo(int32 AmmoAmount, EAmmoType AmmoType);

	void AddToInventory(class AWeaponBase* NewWeapon);

	void EquipWeapon(class AWeaponBase* WeaponToEquip);

	// TODO SwitchToNextInventoryItem(), SwithToPreviousInventoryItem();
	void SwitchToAssault();

	void SwitchToLaser();

	void SwitchToRocket();

	void StartFire();

	void StopFire();

	void SetDataFromSave(const FSaveGameStruct& SaveData);

	FSaveGameStruct GetDataForSave();

	void SpawnInventory(const FSaveGameStruct& SaveData);

	void SetHasKey(bool NewHasKey) { bHasKey = NewHasKey; }

	FORCEINLINE bool IsPlayerHasKey() const { return bHasKey; }
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FName WeaponSocketName = "Weapon";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bEquipNewWeapon : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FPlayerInventory Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Bearing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float MaxHealthPoints = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float HealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float RunSpeed = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsRunning : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bHasKey : 1;


	/** This is a AActor::TakeDamage() overriding
		APawn::TakeDamage - also exists
	*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY()
	AInteractableActor* FocusedActor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 300.f;

	FCollisionQueryParams TraceParams;

	UFUNCTION()
	void HandleHighLight();

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Use();

	UFUNCTION()
	void StartRun();

	UFUNCTION()
	void StopRun();

	UFUNCTION()
	void LookPitch(float Value);

	UFUNCTION()
	void LookYaw(float Value);
	
};
