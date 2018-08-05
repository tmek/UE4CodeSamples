// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventureGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactable.h"
#include "DrawDebugHelpers.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"

//////////////////////////////////////////////////////////////////////////
// AAdventureGameCharacter

AAdventureGameCharacter::AAdventureGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAdventureGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAdventureGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAdventureGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAdventureGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAdventureGameCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AAdventureGameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AAdventureGameCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AAdventureGameCharacter::OnResetVR);

	// interact functionality
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AAdventureGameCharacter::Interact);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AAdventureGameCharacter::StopInteracting);

}


void AAdventureGameCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AAdventureGameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AAdventureGameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}


void AAdventureGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAdventureGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAdventureGameCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAdventureGameCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void AAdventureGameCharacter::Interact()
{
	if (TargetedInteractable)
	{
		IInteractable::Execute_Use(TargetedInteractable);
	}

	if (FollowingNpcCharacter)
	{
		const FVector BeaconLocation = GetActorLocation();
		AAIController *AI = Cast<AAIController>(FollowingNpcCharacter->GetController());

		if (AI)
		{
			UBlackboardComponent* BB = AI->GetBlackboardComponent();
			BB->SetValueAsVector(FName("Beacon"), BeaconLocation);
			BB->SetValueAsBool(FName("IsBeaconActive"), true);
		}
	}
}

void AAdventureGameCharacter::StopInteracting()
{
	if (TargetedInteractable)
	{
		IInteractable::Execute_StopUsing(TargetedInteractable);
	}
}



void AAdventureGameCharacter::Tick(float DeltaSeconds)
{
	TraceInteractables();
}


void AAdventureGameCharacter::TraceInteractables()
{
	if (Controller != NULL && Cast<APlayerController>(Controller))
	{
		// trace through world for interactable in front of character
		float const InteractRange = 200.0f;
		FVector const Location = GetActorLocation();
		FVector const Forward = GetActorForwardVector();
		FVector const End = Location + Forward * InteractRange;

		FHitResult Result;
		GetWorld()->LineTraceSingleByChannel(Result, Location, End, ECollisionChannel::ECC_Visibility);	//  TODO: make a custom trace channel for interactables as an optimization?
		// DrawDebugLine(GetWorld(), Location, End, FColor::Red, false, 3.0f);

		if (Result.bBlockingHit)
		{
			AActor* TracedActor = Result.GetActor();

			if (TargetedInteractable == TracedActor)
			{
				// do nothing if traced actor is currently targeted interactable.
				return;
			}

			if (TracedActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				// unhighlight previous interactable
				if (TargetedInteractable && TargetedInteractable != TracedActor)
				{
					IInteractable::Execute_StopUsing(TargetedInteractable);
					IInteractable::Execute_StopHighlighting(TargetedInteractable);
				}

				// highlight and set new interactable
				TargetedInteractable = TracedActor;
				IInteractable::Execute_Highlight(TargetedInteractable);
			}
		}
		else
		{
			if (TargetedInteractable) 
			{
				// unhighlight and unset previous interactable
				IInteractable::Execute_StopUsing(TargetedInteractable);
				IInteractable::Execute_StopHighlighting(TargetedInteractable);
				TargetedInteractable = nullptr;
			}
		}
	}
}
