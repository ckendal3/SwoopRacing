// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleComponent.h"


// Sets default values for this component's properties
UObstacleComponent::UObstacleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
UObstacleComponent::UObstacleComponent(float healthDeduction, float speedDeduction)
{
	damageAmount = healthDeduction;
	speedReductionAmount = speedDeduction;
}


// Called when the game starts
void UObstacleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UObstacleComponent::DamageSwoopBike(ASwoopPawn* swoopPawn)
{
	swoopPawn->healthComponent->DecreaseHealth(damageAmount);
}

void UObstacleComponent::ReduceSwoopBikeSpeed(ASwoopPawn* swoopPawn)
{
	swoopPawn->DecreaseSpeed(speedReductionAmount);
}

