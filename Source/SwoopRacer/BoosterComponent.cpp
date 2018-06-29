// Fill out your copyright notice in the Description page of Project Settings.

#include "BoosterComponent.h"


// Sets default values for this component's properties
UBoosterComponent::UBoosterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UBoosterComponent::UBoosterComponent(float boostAmount)
{
	speedBoostAmount = boostAmount;
}


// Called when the game starts
void UBoosterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UBoosterComponent::BoostSwoopBike(ASwoopPawn* swoopPawn)
{
	swoopPawn->SpeedBoost(speedBoostAmount);
}

