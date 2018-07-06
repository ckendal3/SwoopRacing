// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwoopPawn.h"
#include "Swoop_PC.h"
#include "CheckPointActor.generated.h"

UCLASS()
class SWOOPRACER_API ACheckPointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPointActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void CheckpointReached(ASwoopPawn* pawn);

	UFUNCTION(BlueprintCallable)
	void FinishLineReached(ASwoopPawn* pawn);
	
};
