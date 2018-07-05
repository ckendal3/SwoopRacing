// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{

}

UHealthComponent::UHealthComponent(float inputHealth)
{
	maxHealth = inputHealth;
	health = inputHealth;
}

/*
// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}*/

void UHealthComponent::IncreaseHealth(float amount, bool allowOverFlow)
{
	if(allowOverFlow || (health + amount) <= maxHealth) // Can override max health or if it will be 
	{
		health += amount;
	}
	healthChanged.Broadcast(health, maxHealth);
}

void UHealthComponent::DecreaseHealth(float amount)
{
	health -= amount;
	healthChanged.Broadcast(health, maxHealth);
}

