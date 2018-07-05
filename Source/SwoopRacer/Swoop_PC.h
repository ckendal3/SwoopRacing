// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Swoop_PC.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLapTimeUpdated, float, lapTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCountdownTimer, float, countdownTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRaceStart, bool, raceStarted);

/**
 * 
 */
UCLASS()
class SWOOPRACER_API ASwoop_PC : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers/Delegates")
		FLapTimeUpdated lapTimeUpdateSignature;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers/Delegates")
		FCountdownTimer countdownUpdateSignature;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers/Delegates")
		FRaceStart raceStartSignature;

	FTimerHandle countDownToStartRaceHandle;
	FTimerHandle lapTimeHandle;


	UFUNCTION()
		virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartRace();
	void UpdateRace();
	void StopRace();

	void StartCountdown();
	void UpdateCountdown();
	void StopCountdown();


	UPROPERTY(EditAnywhere)
	int32 countdownTime = 3;

	int32 lapTime;

	bool raceStarted = false;
	
	
};
