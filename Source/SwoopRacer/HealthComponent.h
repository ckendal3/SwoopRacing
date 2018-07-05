// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChanged, float, currentHealth, float, maxHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWOOPRACER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UHealthComponent(float health);

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	

	UPROPERTY()
	float maxHealth = 100;

	UPROPERTY()
	float health = 100;

	UFUNCTION()
		void IncreaseHealth(float amount, bool allowOverFlow = false);

	UFUNCTION()
		void DecreaseHealth(float amount);

	UPROPERTY(BlueprintAssignable)
		FHealthChanged healthChanged;
};
