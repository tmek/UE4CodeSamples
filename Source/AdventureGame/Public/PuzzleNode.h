// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.h"
#include "PuzzleNode.generated.h"

UENUM(BlueprintType)
enum class EPuzzleNodeState : uint8
{
	Unsolved,
	Solved
};

/**
 *	Puzzle nodes allow level designers to cleanly and easily create interconnected dungeon puzzles 
 *	like those found in Legend of Zelda or Skyrim.
 *	
 *  Leaf nodes are meant to be set 'Solved' through interactions of the player.
 *  Parent nodes automatically evaluate to 'Solved' when all their children are solved.
 *
 *	For example two torches (nodes a and b) might need to be lit for a door (node c) to be unlocked.
 *
 *  The inheriting actor gets to decide what constitutes a puzzle being 'solved'.
 *  They can have their own logic and state that ultimately results in it being solved or unsolved.
 *  
 *  By chaining together many puzzle node actors you can create elaborate puzzle dungeons that
 *  require multiple areas to be solved before the final node is solved.  You can set nodes up to 
 *  allow the player to solve the dungeon puzzles in any order or in a specific order 
 *  (by having nodes prevent access to other areas by using locked doors, draw bridges etc.)
 *  
 *  Examples: 
 *		- one or more simple torches, levers or switches that must be lit, pulled or pressed
 *		- a series statues that must be rotated to show certain images
 *		- a combination lock that must be dialed to a certain number or series of glyphs
 *		- a pedestal or area the player must move some other specified object onto
 *		- combinations of the above:
 *			- a statue that must be rotated a certain way in along with pulling a momentary lever to check it.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENTUREGAME_API APuzzleNode : public AInteractableActor
{
	GENERATED_BODY()

public:	
	/** Sets default values for this component's properties */
	APuzzleNode();

	/** Current solved state of this node */
	UPROPERTY(VisibleAnywhere, Category = "Puzzle Nodes")
	EPuzzleNodeState State;

	/** 
	 * The children of this puzzle node.  
	 * Use eyedropper button to select puzzle node actors from the editor viewport 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle Nodes")
	TArray<TSoftObjectPtr<APuzzleNode>> ChildNodes;

	/** Parent puzzle node of this node. */
	UPROPERTY()
	APuzzleNode* Parent;

	/** Called when this puzzle node has changed to solved */
	UFUNCTION(BlueprintImplementableEvent, Category = "Puzzle Nodes")
	void OnSolved();

	/** Called when this puzzle node has changed to unsolved */
	UFUNCTION(BlueprintImplementableEvent, Category = "Puzzle Nodes")
	void OnUnsolved();

	/** Current solved state of this node */
	UFUNCTION(BlueprintCallable, Category = "Puzzle Nodes")
	void SetState(EPuzzleNodeState NewState);

	/** Returns true if this node is solved */
	UFUNCTION(BlueprintCallable, Category = "Puzzle Nodes")
	bool GetIsSolved();

	/** Sets this node to solved or unsolved */
	UFUNCTION(BlueprintCallable, Category = "Puzzle Nodes")
	void SetIsSolved(bool IsSolved);


protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Determines if this node is implicitly solved based on the state of it's children */
	void EvaluateChildren();

	/** Called when the solved state of this node changes */
	void OnStateChanged();

	/** Called when the children of this node are modified */
	void OnChildrenModified();
};
