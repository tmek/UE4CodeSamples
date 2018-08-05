// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "InteractableComponent.h"
#include "ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Components/PostProcessComponent.h"

UInteractionComponent::UInteractionComponent() 
{
	// set class defaults
	PrimaryComponentTick.bCanEverTick = true;
	TraceChannel = ECC_Visibility;
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;
	InteractionDistance = 1000.0f;

	// find reference to highlight post process material.  
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightPostProcessMaterialFinder(TEXT("/Game/Environment/PostProcess/PPI_OutlineColored"));
	HighlightPostProcessMaterial = HighlightPostProcessMaterialFinder.Object;

	// add post process component 
	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Interaction Post Process"), true);
	PostProcessComponent->bUnbound = true;
	PostProcessComponent->AddOrUpdateBlendable(HighlightPostProcessMaterial, 1.0f);

}

void UInteractionComponent::Interact()
{
	if (FocusedInteractableComponent)
	{
		FocusedInteractableComponent->OnBeginInteract.Broadcast(this);
	}
}

void UInteractionComponent::StopInteracting()
{
	if (FocusedInteractableComponent)
	{
		FocusedInteractableComponent->OnEndInteract.Broadcast(this);
	}
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PerformTrace();
}

void UInteractionComponent::PerformTrace()
{
	auto Camera = UGameplayStatics::GetPlayerCameraManager(this, 0);

	FVector Forward = UKismetMathLibrary::GetForwardVector(Camera->GetCameraRotation());
	FVector Start = Camera->GetCameraLocation();
	FVector End = Start + Forward * InteractionDistance;

	FHitResult OutHit;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(TraceChannel), false, TArray<AActor *>(), EDrawDebugTrace::ForOneFrame, OutHit, true);

	UInteractableComponent* OldInteractableComponent = FocusedInteractableComponent;
	FocusedInteractableComponent = nullptr;

	if (bHit)
	{
		FocusedInteractableComponent = OutHit.GetActor()->FindComponentByClass<UInteractableComponent>();
	}

	// did Interactable Change?
	if (OldInteractableComponent != FocusedInteractableComponent)
	{
		if (FocusedInteractableComponent)
		{
			FocusedInteractableComponent->Highlight();
		}

		if (OldInteractableComponent)
		{
			// if the player aims away from a previously highlighted interactable,
			// we want to ensure we're no longer interacting with it
			OldInteractableComponent->StopHighlighting();
			OldInteractableComponent->OnEndInteract.Broadcast(this);
		}
	}
}