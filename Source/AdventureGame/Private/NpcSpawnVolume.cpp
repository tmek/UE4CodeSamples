// Fill out your copyright notice in the Description page of Project Settings.

#include "NpcSpawnVolume.h"
#include "AdventureGameCharacter.h"
#include "AdventureGameAIController.h"
#include "Components/BrushComponent.h"


void ANpcSpawnVolume::SpawnCharacterInstance(const FVector& Location, const FRotator& Rotation)
{
	// spawn character instance
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACharacter* Character = GetWorld()->SpawnActor<ACharacter>(TemplateCharacter, Location, Rotation, Parameters);

	// optionally spawn character AI
	if (bShouldSpawnAI)
	{
		AAdventureGameAIController* AI = GetWorld()->SpawnActor<AAdventureGameAIController>();
		AI->Possess(Character);
	}
}

void ANpcSpawnVolume::BeginPlay() 
{
	// construct bounding box
	FVector const BoxOrigin = GetBrushComponent()->Bounds.Origin;
	FVector const BoxExtent = GetBrushComponent()->Bounds.BoxExtent;
	FBox const VolumeBox = FBox(BoxOrigin - BoxExtent, BoxOrigin + BoxExtent);

	// spawn npcs
	for (int i = 0; i < SpawnCount; i++)
	{
		FVector const Location = FMath::RandPointInBox(VolumeBox);
		float const Yaw = FMath::RandRange(0, 360);
		FRotator const Rotation = FRotator(0, Yaw, 0);

		// trace down to ground
		FVector const End = Location + FVector(0, 0, -1) * 5000.0f;
		FHitResult Result;
		GetWorld()->LineTraceSingleByChannel(Result, Location, End, ECollisionChannel::ECC_Camera);

		// spawn a character instance
		SpawnCharacterInstance(Result.Location + FVector(0, 0, 94) , Rotation);
	}
}