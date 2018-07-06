// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HealthComponent.h"
#include "Components/InputComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "SwoopPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpeedChange, float, currentSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShiftReady, bool, bReadyToShift);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDied, bool, playerIsDead);

UCLASS()
class SWOOPRACER_API ASwoopPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASwoopPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers/Delegates")
		FSpeedChange SpeedChangeSignature;
	
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers/Delegates")
		FShiftReady ShiftingSignature;
	
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers/Delegates")
	FPlayerDied PlayerDiedSignature;

	UPROPERTY(BlueprintReadWrite)
		UHealthComponent* healthComponent;

	UFUNCTION()
		void SpeedBoost(float speedBoost);
	UFUNCTION()
		void IncreaseSpeed();
	UFUNCTION()
		void DecreaseSpeed(float decreaseAmount);
	UFUNCTION()
		void ShiftGears();
	UFUNCTION()
		void MoveHorizontal(float AxisValue);
	UFUNCTION()
		void MoveForward();

	UFUNCTION()
		void ChangeHealth(float amount, bool positive = false);
	UPROPERTY()
		float speed = 0.0f;
	UPROPERTY(EditAnywhere)
		float accelerationRate = 6.0f;
	UPROPERTY(BlueprintReadOnly)
		int currentGear = 0;
	UPROPERTY(EditAnywhere)
		int MAXGEARS = 6;
	UPROPERTY(EditAnywhere)
		float badShiftDecrease = 10;
	UPROPERTY(EditAnywhere)
		float horizontalMovementSpeed = 10;
	UPROPERTY(EditAnywhere)
		float MAXSPEEDPERGEAR = 50;
	UPROPERTY(EditAnywhere)
		USoundCue* propellerAudioCue;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* propellerAudioComponent;

	UPROPERTY(EditAnywhere)
		UBoxComponent* rootCollision;

	//UPROPERTY(EditAnywhere)
		//UMeshComponent* swoopMesh;

	FVector newLocation;

	UFUNCTION()
		void CalculateShift();

	UFUNCTION()
		void RestartMap();

	UFUNCTION()
		void GameStop();

	bool isAlive = true;

	bool readyToShift = true; // is true so you have to shift to start moving
	
};
