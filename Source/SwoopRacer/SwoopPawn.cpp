// Fill out your copyright notice in the Description page of Project Settings.

#include "SwoopPawn.h"


// Sets default values
ASwoopPawn::ASwoopPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// used for health
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	propellerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));
	
	rootCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RootCollision"));
	rootCollision->SetBoxExtent(FVector(200, 128, 32), true);
	RootComponent = rootCollision;

	propellerAudioComponent->SetupAttachment(RootComponent);

	//swoopMesh = CreateDefaultSubobject<UMeshComponent>(TEXT("SwoopMesh"));

}

// Called when the game starts or when spawned
void ASwoopPawn::BeginPlay()
{
	Super::BeginPlay();
	
	propellerAudioComponent->SetSound(propellerAudioCue);

	// Set this pawn to be controlled by the first player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	newLocation = GetActorLocation(); // this is fine

	propellerAudioComponent->Play();
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
	

	if (timeSinceLastCall >= .25f) // Speed up every half second
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
	InputComponent->BindAction("Restartmap", IE_Pressed, this, &ASwoopPawn::RestartMap);

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
	propellerAudioComponent->SetPitchMultiplier(speed / 10);
	SpeedChangeSignature.Broadcast(speed);
}

//Decrease Speed
void ASwoopPawn::DecreaseSpeed(float decreaseAmount) // Needs to point slightly down
{
	
	if ((speed - decreaseAmount) *currentGear <= 0) // Don't ever decrease speed to zero or less
	{
		speed = 1;
	}
	else
	{
		speed -= decreaseAmount; // decrease speed for bad shift and the higher the gear the worse the penalty
	}
	propellerAudioComponent->SetPitchMultiplier(speed / 10);
	SpeedChangeSignature.Broadcast(speed);
}

// Big Speed Boost
void ASwoopPawn::SpeedBoost(float speedBoost) // Needs to Tilt Slightly up
{
	// player needs to shift. Do nothing till shifted
	if (readyToShift)
	{
		speed += speedBoost / 4;
	}
	speed += speedBoost;
	propellerAudioComponent->SetPitchMultiplier(speed / 10);
	SpeedChangeSignature.Broadcast(speed);
}

//Shift gears to build more speed
void ASwoopPawn::ShiftGears()
{
	if (readyToShift)
	{
		currentGear += 1;
		SpeedBoost(10); // boost off every gear change
		readyToShift = false;
		ShiftingSignature.Broadcast(readyToShift);
		return; // need to shift to gain more speed
	}
	else if(currentGear != 0)
	{
		DecreaseSpeed(badShiftDecrease + (2 * currentGear)); // decrease speed for bad shift and the higher the gear the worse the penalty
		ShiftingSignature.Broadcast(readyToShift);
	}
}

void ASwoopPawn::MoveForward() // Needs to rotate slightly depending on axis
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
	PlayerDiedSignature.Broadcast(isAlive);
}

void ASwoopPawn::CalculateShift()
{
	// Speed divided by the gear is more than 50, then player needs to shift
	if ((speed / currentGear) >= 50 && currentGear <= MAXGEARS)
	{
		readyToShift = true;
		ShiftingSignature.Broadcast(readyToShift);
	}
	else if ((speed / (currentGear - 1) < 50 && currentGear > 1)) // Auto DownShift if low speed from being bad
	{
		currentGear -= 1;
		readyToShift = false;
		ShiftingSignature.Broadcast(readyToShift);
	}
}

void ASwoopPawn::GameStop()
{
	// Call pause game or pause menu or game over screen
}

// Debug Tool to restart level
void ASwoopPawn::RestartMap()
{
	//FName mapName = GetWorld()->GetMapName();
	UGameplayStatics::OpenLevel((UObject*)GetWorld(), "SwoopTest", true); 
}

