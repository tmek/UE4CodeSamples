// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventureGameAIController.h"
#include "DrawDebugHelpers.h"
#include "AdventureGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void AAdventureGameAIController::SetRandomTickInterval()
{
	SetActorTickInterval(FMath::RandRange(MinDelay, MaxDelay));
}

void AAdventureGameAIController::BeginPlay()
{
	SetRandomTickInterval();
	SetActorTickEnabled(true);
	Super::BeginPlay();
}

void AAdventureGameAIController::PickRandomDestination()
{
	// pick a new random destination within MaxRadius
	AAdventureGameCharacter* Character = (AAdventureGameCharacter*)GetCharacter();
	if (Character)
	{
		const FRotator Rotator(0, FMath::RandRange(0.0f, 360.0f), 0);
		const FVector NewDirection = Rotator.RotateVector(Character->GetActorForwardVector());
		Destination = Character->GetActorLocation() + NewDirection * FMath::RandRange(0.0f, MaxRange);

		if (bShouldDrawDebug)
		{
			DrawDebugSphere(GetWorld(), Destination, 24, 32, FColor(255, 0, 0), false, this->GetActorTickInterval());
		}
	}
}

void AAdventureGameAIController::MoveToDestination()
{
	// move to destination
	AAdventureGameCharacter* Character = (AAdventureGameCharacter*)GetCharacter();
	if (Character)
	{
		UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
		Movement->MaxWalkSpeed = 94.0f;

		MoveToLocation(Destination, -1.0f, true, false);
	}
}

void AAdventureGameAIController::Tick(float DeltaTime)
{
	PickRandomDestination();

	MoveToDestination();

	SetRandomTickInterval();
}

void AAdventureGameAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	// UE_LOG(LogTemp, Warning, TEXT("MoveCompleted "));
}
