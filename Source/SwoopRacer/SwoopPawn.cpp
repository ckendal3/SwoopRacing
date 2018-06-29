// Fill out your copyright notice in the Description page of Project Settings.

#include "SwoopPawn.h"

// Sets default values
ASwoopPawn::ASwoopPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// used for health
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ASwoopPawn::BeginPlay()
{
	Super::BeginPlay();

	// Set this pawn to be controlled by the first player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	newLocation = GetActorLocation(); // this is fine
}

// Called every frame
void ASwoopPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Add up the times between the last call
	timeSinceLastCall += DeltaTime;

	if (currentGear > 0)
	{
		MoveForward();
	}
	

	if (timeSinceLastCall >= .5f) // Speed up every half second
	{	
		CalculateShift(); // Check if player needs to shift
		IncreaseSpeed();
		timeSinceLastCall = 0; // restart timer
	}
}

// Called to bind functionality to input
void ASwoopPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &ASwoopPawn::MoveHorizontal);
	InputComponent->BindAction("ShiftGear", IE_Pressed, this, &ASwoopPawn::ShiftGears);

}

//Function to steadily increase speed over time
void ASwoopPawn::IncreaseSpeed()
{
	// player needs to shift. Do nothing till shifted
	if (readyToShift)
	{
		return;
	} 

	speed += accelerationRate/currentGear; // accelerartion rate drops in higher gears
}

//Decrease Speed
void ASwoopPawn::DecreaseSpeed(float decreaseAmount)
{
	speed -= decreaseAmount;
}

// Big Speed Boost
void ASwoopPawn::SpeedBoost(float speedBoost)
{
	speed += speedBoost;
}

//Shift gears to build more speed
void ASwoopPawn::ShiftGears()
{
	if (readyToShift)
	{
		currentGear += 1;
		SpeedBoost(10); // boost off every gear change
		readyToShift = false;
		return; // need to shift to gain more speed
	}
	else if(currentGear)
	{
		if ((speed - badShiftDecrease) *currentGear <= 0) // Don't ever decrease speed to zero or less
		{
			speed = 1;
		}
		else
		{
			DecreaseSpeed(badShiftDecrease *currentGear); // decrease speed for bad shift and the higher the gear the worse the penalty
		}
	}
}

void ASwoopPawn::MoveForward()
{
	newLocation += (GetActorForwardVector()) * speed;
	SetActorLocation(newLocation, true);
}

// Move side to side
void ASwoopPawn::MoveHorizontal(float AxisValue)
{
	newLocation += (GetActorRightVector() * FMath::Clamp(AxisValue, -1.0f, 1.0f)) * horizontalMovementSpeed;
	SetActorLocation(newLocation, true);
}

// Change health for hitting obstacles (or future implementations)
void ASwoopPawn::ChangeHealth(float amount, bool isIncreasing)
{
	if(isIncreasing)
	{
		healthComponent->IncreaseHealth(amount);
	}
	else
	{
		healthComponent->DecreaseHealth(amount);
		if (healthComponent->health <= 0)
		{
			isAlive = false;
		}
	}
}

void ASwoopPawn::CalculateShift()
{
	// Speed divided by the gear is more than a hundred then player needs to shift
	if ((speed / currentGear) >= 50 && currentGear <= MAXGEARS)
	{
		readyToShift = true;
	}
}

