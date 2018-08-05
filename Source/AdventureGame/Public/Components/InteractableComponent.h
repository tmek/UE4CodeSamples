// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class UMeshComponent;
class UInteractionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeginInteractSignature, UInteractionComponent*, InteractionComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndInteractSignature, UInteractionComponent*, InteractionComponent);

/**
 * The interactable component enables owning actor to be "interactable".
 * 
 * Provides methods to highlight the interactable actor and events to begin and end interacting with it. 
 */ 
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), config = FooAdventureGame, defaultconfig)
class ADVENTUREGAME_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Called when an interaction component begins interacting with owning actor. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Event")
	FBeginInteractSignature OnBeginInteract;

	/** Called when an interaction component ends interacting with owning actor. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Event")
	FEndInteractSignature OnEndInteract;

	/** Depth stencil value to use for post process highlight material. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Interaction")  
	int HighlightDepthStencilValue = 252; 

	/** Highlight the owning actor. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Highlight();  

	/** Stop highlighting the owning actor. */
	UFUNCTION(BlueprintCallable, Category = "Interaction") 
	void StopHighlighting(); 

protected:
	// cached array of all mesh components of owning actor.
	UPROPERTY(Transient)
	TArray<UMeshComponent*> HighlightComponents;

	virtual void BeginPlay() override;
};
