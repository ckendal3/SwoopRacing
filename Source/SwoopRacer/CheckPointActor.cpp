// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckPointActor.h"


// Sets default values
ACheckPointActor::ACheckPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckPointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckPointActor::FinishLineReached(ASwoopPawn* pawn)
{
	ASwoop_PC* player = (ASwoop_PC*) pawn->GetController();

	if (player != nullptr)
	{
		player->StopRace();

		// do something better for slowing down over 3 seconds
		pawn->DecreaseSpeed(1000); // Do something else in the future
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

