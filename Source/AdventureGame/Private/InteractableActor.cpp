// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableActor.h"
#include "Components/StaticMeshComponent.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	// cache reference to child static mesh components
	GetComponents<UStaticMeshComponent>(MeshComponents);

	// ensure custom depth stencil value is set for child static mesh components
	for (UStaticMeshComponent* Mesh : MeshComponents)
	{
		Mesh->SetCustomDepthStencilValue(HighlightDepthStencilValue);  // TODO: no magic numbers
	}
}

void AInteractableActor::Highlight_Implementation()
{
	for (UStaticMeshComponent* Mesh : MeshComponents)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AInteractableActor::StopHighlighting_Implementation()
{
	for (UStaticMeshComponent* Mesh : MeshComponents)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}
