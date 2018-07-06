// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoop_PC.h"


void ASwoop_PC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If input received before countdown timer is done, disqualified
	if(raceStarted)
	{
		UpdateRace(); // Update Laptime
	}
}


void ASwoop_PC::BeginPlay()
{
	Super::BeginPlay();

	StartCountdown();
}

// Start laptime and delegate
void ASwoop_PC::StartRace()
{
	raceStartSignature.Broadcast(raceStarted);
}

// Update LapTime Every Call
void ASwoop_PC::UpdateRace()
{
	lapTimeUpdateSignature.Broadcast(lapTime += GetWorld()->GetDeltaSeconds());
}

// Race is over so do stuff
void ASwoop_PC::StopRace()
{
	raceStarted = false;
	SetActorTickEnabled(false);

	//-------For Menus-------//
	//SetPause(true);
	//bShowMouseCursor = true;

	if (raceSuccess)
	{
		RaceWon();
	}
	else if (raceFailure)
	{
		RaceFailed();
	}
}

// Start beginning match countdown to start race
void ASwoop_PC::StartCountdown()
{
	GetWorldTimerManager().SetTimer(countDownToStartRaceHandle, this, &ASwoop_PC::UpdateCountdown, 1.0f, true);
}

// Update every second for the countdown
void ASwoop_PC::UpdateCountdown()
{
	--countdownTime;
	if (countdownTime < 1)
	{
		StopCountdown();
		return;
	}
	countdownUpdateSignature.Broadcast(countdownTime);
}

// Countdown is finished
void ASwoop_PC::StopCountdown()
{
	// Clear timer
	GetWorldTimerManager().ClearTimer(countDownToStartRaceHandle);

	// Start Race
	raceStarted = true;
	StartRace();
}

void ASwoop_PC::RaceWon()
{
	//Save Time if good enough
	//Display win menu
}

void ASwoop_PC::RaceFailed()
{
	//Discard LapTime
	//Display Lost Menu
}




