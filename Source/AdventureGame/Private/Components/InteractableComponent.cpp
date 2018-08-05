// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableComponent.h"
#include "Components/MeshComponent.h"

void UInteractableComponent::Highlight()
{
	for (auto component : HighlightComponents) 
	{
		component->SetRenderCustomDepth(true);
	}
}

void UInteractableComponent::StopHighlighting()
{
	for (auto component : HighlightComponents)
	{
		component->SetRenderCustomDepth(false);
	}
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// cache array of owning actor's mesh components for highlighting 
	// #fixme should this be done postconstruction rather than begin play?
	//	(read up on AActor::OnConstruction // UActorComponent::OnComponentCreated
	//	 basically we'd need it to run anytime we were attached to an actor.
	//	 or our actor changed components.)
	AActor *Owner = GetOwner();
	Owner->GetComponents<UMeshComponent>(HighlightComponents);

	// set custom stencil value used for highlighting
	for (UMeshComponent *component : HighlightComponents)
	{
		component->SetCustomDepthStencilValue(HighlightDepthStencilValue);
	}
}