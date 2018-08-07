// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractionComponent.generated.h"

class UInteractableComponent;
class UMaterialInterface;
class UPostProcessComponent;

/**
 *  Traces for closest actor having an interactable component.
 *  If found, sets it as the focused interactable and highlights it. 
 *  Provides interact and stop interacting methods for the focused interactable actor.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENTUREGAME_API UInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	/** The post process material to use for highlighting interactable actors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	UMaterialInterface* HighlightPostProcessMaterial;

	/** The distance in game units the component should be able to interact with a interactable component. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionDistance;

	/** The trace channel to use when tracing for interactable components in the world.	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	/** Start interacting with current interactable. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	/** Stop interacting with current interactable. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void StopInteracting();

	/** Gets the currently focused actor. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AActor* GetCurrentlyFocusedActor();

	/** The last hit result we used. */
	UPROPERTY(BlueprintReadOnly, Transient)
	FHitResult LastHitResult;

protected:
	/** The currently focused interactable component if any. */
	UPROPERTY(Transient)
	UInteractableComponent* FocusedInteractableComponent;

	/** The post process component to apply the highlight effect. */
	UPROPERTY(Transient)
	UPostProcessComponent* PostProcessComponent;

	/** Trace for an actor with an InteractableComponent */
	void PerformTrace();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
