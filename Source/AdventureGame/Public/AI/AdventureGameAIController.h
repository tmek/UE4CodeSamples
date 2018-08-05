// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AdventureGameAIController.generated.h"

/**
 * NPC AI controller that can select a new random destination and move to it with a random delay.
 */
UCLASS()
class ADVENTUREGAME_API AAdventureGameAIController : public AAIController
{
	GENERATED_BODY()
	
public:	
	/** The destination the AI will move to */
	UPROPERTY(BlueprintReadonly)
	FVector Destination;

	/** The minimum delay between moves */
	UPROPERTY(EditAnywhere)
	float MinDelay = 1.0f;

	/** The maximum delay between moves */
	UPROPERTY(EditAnywhere)
	float MaxDelay = 10.0f;

	/** The maximum range of the next random destination */
	UPROPERTY(EditAnywhere)
	float MaxRange = 500.0f;

	/** Enable to draw debug sphere at destination */
	UPROPERTY(EditAnywhere)
	bool bShouldDrawDebug = false;

	/** Picks a random destination within max range */
	UFUNCTION(BlueprintCallable)
	void PickRandomDestination();

	/** Moves to the destination location */
	UFUNCTION(BlueprintCallable)
	void MoveToDestination();

protected:
	/** Sets the next tick interval between min and max delay */
	void SetRandomTickInterval();

	/** Called when the game begins */
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result) override;

};
