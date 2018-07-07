// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckPointActor.h"


// Sets default values
ACheckPointActor::ACheckPointActor()
{

}

// Called when the game starts or when spawned
void ACheckPointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckPointActor::FinishLineReached(ASwoopPawn* pawn)
{
	ASwoop_PC* player = (ASwoop_PC*) pawn->GetController();

	if (player != nullptr)
	{
		//Call RaceSuccess which Calls StopRace

		player->raceSuccess = true;
		player->StopRace();

		// do something better for slowing down over 3 seconds
		//pawn->speed = 0; // Do something else in the future
		pawn->currentGear = 0;
	}
}

void ACheckPointActor::CheckpointReached(ASwoopPawn* pawn)
{
	ASwoop_PC* player = (ASwoop_PC*)pawn->GetController();

	if (player != nullptr)
	{
		// Display best laptime
	}
}

