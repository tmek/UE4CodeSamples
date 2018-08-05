// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "NpcSpawnVolume.generated.h"

class AAdventureGameCharacter;

/**
 * A simple volume that spawns a random distribution of NPCs, optionally with AI.
 */
UCLASS()
class ADVENTUREGAME_API ANpcSpawnVolume : public AVolume
{
	GENERATED_BODY()
	
public:		
	
	/** Number of NPCs to spawn */
	UPROPERTY(EditAnywhere)
	int32 SpawnCount = 10;

	/** Template character used for each spawn instance */
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> TemplateCharacter;
	
	/** Should characters be spawned with AI */
	UPROPERTY(EditAnywhere)
	bool bShouldSpawnAI;

	/** Called when the game begins */
	virtual void BeginPlay() override;

private:
	/** Spawns a character instance */
	void SpawnCharacterInstance(const FVector & Location, const FRotator & Rotation);
};
