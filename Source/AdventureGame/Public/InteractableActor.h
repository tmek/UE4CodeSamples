// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractableActor.generated.h"

/**
 * An actor that can be interacted with by the player.
 *
 * It can be a focal point of the player and can respond to player use and stop using events.
 */
UCLASS()
class ADVENTUREGAME_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

	// Called when this actor becomes the focus of the player
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void Highlight();

	// Called when this actor is no longer the focus of the player
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void StopHighlighting();

protected:
	TArray<UStaticMeshComponent*> MeshComponents;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Default highlighting implementation
	virtual	void Highlight_Implementation() override;

	// Default stop highlight implementation
	virtual	void StopHighlighting_Implementation() override;

	// Value to draw to the stencil depth buffer for highlight effect
	int HighlightDepthStencilValue = 252;
};
