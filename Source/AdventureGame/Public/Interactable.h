// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to an interactable object.
 * 
 * Interactables can become the focus of the player and respond to player use and stop using events.
 */
class ADVENTUREGAME_API IInteractable
{
	GENERATED_BODY()

public:
	// Called when the player begins using this object.
	UFUNCTION(BlueprintImplementableEvent, Category = "Interactable")
	void Use();

	// Called when the player stops using this object.
	UFUNCTION(BlueprintImplementableEvent, Category = "Interactable")
	void StopUsing();

	// Called when this object becomes the focus of the player.
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void Highlight();

	// Called when this object is no longer the focus of the player.
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void StopHighlighting();
};
