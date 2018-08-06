// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleNode.h"


// Sets default values for this actor's properties
APuzzleNode::APuzzleNode()
{
	PrimaryActorTick.bCanEverTick = false;
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
	return (State == EPuzzleNodeState::Solved);
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

void APuzzleNode::EvaluateChildren()
{
	EPuzzleNodeState NewState = EPuzzleNodeState::Solved;

	// new state should be unsolved if any children are unsolved
	for (TSoftObjectPtr<APuzzleNode> PuzzleNode : ChildNodes)
	{
		if (PuzzleNode->State == EPuzzleNodeState::Unsolved) 
		{
			NewState = EPuzzleNodeState::Unsolved;
			break;
		}
	}

	// notify if state changes
	if (State != NewState)
	{
		State = NewState;
		OnStateChanged();
	}
}

void APuzzleNode::OnStateChanged()
{
	// anytime a child node changes we check siblings to determine derived state of parent
	// these changes can bubble up the puzzle node tree. (EvaluateChildren and OnStateChanged are mutually recursive)
	if (Parent)
	{
		Parent->EvaluateChildren();
	}

	// notify event subscribers of state change
	if (State == EPuzzleNodeState::Solved) 
	{
		this->OnSolved();
	}
	else
	{
		this->OnUnsolved();
	}
}

void APuzzleNode::OnChildrenModified()
{
	// ensure children have a reference back to their parent
	for (auto PuzzleNode : ChildNodes)
	{
		PuzzleNode->Parent = this;
	}
}
