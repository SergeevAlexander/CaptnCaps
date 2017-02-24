﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "MyPlayer.h"
#include "InteractableActor.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TraceParams = FCollisionQueryParams(TEXT("TraceParams"), false, this);
	TraceParams.bTraceComplex = false;
	TraceParams.bTraceAsyncScene = false;
	TraceParams.bReturnPhysicalMaterial = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.f;

	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->RelativeRotation = FRotator(-90.f, 0.f, 0.f);

	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);


	
	bIsRunning = false;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	HealthPoints = MaxHealthPoints;
}

// Called every frame
void AMyPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// HighLight only for this particular player
	if (Controller && Controller->IsLocalController())
	{
		HandleHighLight();
		GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::Red, FString::Printf(TEXT("HP: %f"), HealthPoints));
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
	InputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
	InputComponent->BindAxis("LookYaw", this, &AMyPlayer::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &AMyPlayer::LookPitch);

	InputComponent->BindAction("Use", IE_Pressed, this, &AMyPlayer::Use);
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayer::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyPlayer::StopRun);

}

float AMyPlayer::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	HealthPoints -= ActualDamage;

	if (HealthPoints <= 0)
	{
		OnDeath();
	}

	return ActualDamage;
}


AInteractableActor* AMyPlayer::FindFocusedActor()
{
	if (!Controller)
	{
		return nullptr;
	}

	FVector Location;
	FRotator Rotation;
	FHitResult Hit(ForceInit);

	Controller->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + GetActorForwardVector() * InteractionDistance;

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);
	
	
	if (Hit.bBlockingHit)
	{
		AInteractableActor* InteractableActor = Cast<AInteractableActor>(Hit.GetActor());
		if (InteractableActor)
		{
			return InteractableActor;
		}
	}

	return nullptr;
}

void AMyPlayer::OnDeath()
{
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("You died!")));
	Destroy();
}

void AMyPlayer::Heal(float Amount)
{
	if (Amount > 0)
	{
		HealthPoints += Amount;
		if (HealthPoints > MaxHealthPoints)
		{
			HealthPoints = MaxHealthPoints;
		}
	}
}

void AMyPlayer::HandleHighLight()
{
	AInteractableActor* NewHighLight = FindFocusedActor();

	if (NewHighLight)
	{
		if (NewHighLight != FocusedActor)
		{
			if (FocusedActor)
			{
				FocusedActor->OnEndFocus();
			}
			
			NewHighLight->OnBeginFocus();
			FocusedActor = NewHighLight;
		}
	}
	else
	{
		if (FocusedActor)
		{
			FocusedActor->OnEndFocus();
		}
		FocusedActor = nullptr;
	}
	
}

void AMyPlayer::MoveForward(float Value)
{
	// FVector ForwardVector = GetActorForwardVector(); // FPS TPS
	FVector ForwardVector(1.f, 0.f, 0.f);
	AddMovementInput(ForwardVector, Value);
}

void AMyPlayer::MoveRight(float Value)
{
	//FVector RightVector = GetActorRightVector();
	FVector RightVector(0.f, 1.f, 0.f);
	AddMovementInput(RightVector, Value);
}

void AMyPlayer::LookPitch(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyPlayer::LookYaw(float Value)
{
	AddControllerYawInput(Value);
}

void AMyPlayer::Use()
{
	AInteractableActor* InteractableActor = FindFocusedActor();
	if (InteractableActor)
	{
		InteractableActor->OnInteract(this);
	}
}

void AMyPlayer::StartRun()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMyPlayer::StopRun()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

