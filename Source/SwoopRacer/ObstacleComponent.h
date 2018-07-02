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

	UPROPERTY(EditAnywhere)
		float damageAmount = 25;
		
	UPROPERTY(EditAnywhere)
		float speedReductionAmount = 10;
	
	UFUNCTION(BlueprintCallable)
	void DamageSwoopBike(ASwoopPawn* swoopPawn);

	UFUNCTION(BlueprintCallable)
		void ReduceSwoopBikeSpeed(ASwoopPawn* swoopPawn);
};
