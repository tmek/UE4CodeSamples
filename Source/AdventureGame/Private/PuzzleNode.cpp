// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleNode.h"


// Sets default values for this component's properties
APuzzleNode::APuzzleNode()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void APuzzleNode::SetState(EPuzzleNodeState NewState)
{
	if (State != NewState)
	{
		State = NewState;
		OnStateChanged();
	}
}

bool APuzzleNode::GetIsSolved()
{
	return State == EPuzzleNodeState::Solved;
}

void APuzzleNode::SetIsSolved(bool IsSolved)
{
	if (IsSolved)
	{
		SetState(EPuzzleNodeState::Solved);
	}
	else
	{
		SetState(EPuzzleNodeState::Unsolved);
	}
}

// Called when the game starts
void APuzzleNode::BeginPlay()
{
	Super::BeginPlay();

	OnChildrenModified();
}

//APuzzleNode* APuzzleNode::GetPuzzleNode(AActor* Actor) 
//{
//	TArray<APuzzleNode*> Components;
//	Actor->GetComponents<APuzzleNode>(Components);
//
//	return Components[0];
//}

void APuzzleNode::EvaluateChildren()
{
	EPuzzleNodeState NewState = EPuzzleNodeState::Solved;

	// set newstate unsolved if any children are unsolved.
	for (auto PuzzleNode : ChildNodes)
	{
		//APuzzleNode* Node = GetPuzzleNode(Child);

		if (PuzzleNode->State == EPuzzleNodeState::Unsolved) 
		{
			NewState = EPuzzleNodeState::Unsolved;
			break;
		}
	}

	// notify if state changed.
	if (State != NewState)
	{
		State = NewState;
		OnStateChanged();
	}
}

void APuzzleNode::OnStateChanged()
{
	if (Parent)
	{
		Parent->EvaluateChildren();
	}
	
	if (State == EPuzzleNodeState::Solved) 
	{
		//OnSolved.Broadcast();
		this->OnSolved();
	}
	else
	{
		//OnUnsolved.Broadcast();
		this->OnUnsolved();
	}
}

void APuzzleNode::OnChildrenModified()
{
	// iterate children and set their parent property to this.
	for (auto PuzzleNode : ChildNodes)
	{
		PuzzleNode->Parent = this;
	}
}
