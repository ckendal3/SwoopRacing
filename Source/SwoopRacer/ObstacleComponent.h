// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SwoopPawn.h"
#include "ObstacleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWOOPRACER_API UObstacleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObstacleComponent();
	UObstacleComponent(float damageAmount, float speedDeduction);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY()
		float damageAmount = 25;
		
	UPROPERTY()
		float speedReductionAmount = 10;
	
	UFUNCTION()
	void DamageSwoopBike(ASwoopPawn* swoopPawn);

	UFUNCTION()
		void ReduceSwoopBikeSpeed(ASwoopPawn* swoopPawn);


		
	
};
