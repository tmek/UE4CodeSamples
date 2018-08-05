// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindLocation.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"


EBTNodeResult::Type UBTTask_FindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AI = Cast<AAIController>(OwnerComp.GetOwner());

	// pick a new random destination within MaxRadius
	ACharacter* Character = (ACharacter*)AI->GetCharacter();

	if (AI && Character)
	{
		const float MaxRange = 500.0f;
		const float MinRange = 300.0f;
		const FRotator Rotator(0, FMath::RandRange(0.0f, 360.0f), 0);
		const FVector NewDirection = Rotator.RotateVector(Character->GetActorForwardVector());
		const FVector Destination = Character->GetActorLocation() + NewDirection * FMath::RandRange(MinRange, MaxRange);

		DrawDebugSphere(GetWorld(), Destination, 24, 32, FColor(255, 0, 0), false, 3.0f);

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Destination);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
