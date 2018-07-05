// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoop_PC.h"


void ASwoop_PC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If input received before countdown timer is done, disqualified
	if (!raceStarted)
	{
		
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

	GetWorldTimerManager().SetTimer(lapTimeHandle, this, &ASwoop_PC::UpdateRace, 1.f, true);

}

// Update LapTime Every Call
void ASwoop_PC::UpdateRace()
{
	lapTime += 1;
	lapTimeUpdateSignature.Broadcast(lapTime);
}

// Race is over so do stuff
void ASwoop_PC::StopRace()
{
	// Stop LapTIme
	// Save if good
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



