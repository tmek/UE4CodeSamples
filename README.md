# UE4CodeSamples

Hi! This project is meant to demonstrate Unreal Engine 4 project organization and coding proficiency.

The sample project adheres to a coding standard.  In this case: <br/>
https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard

## Overview

This project showcases two features.  A player interaction system and a puzzle node system.

### Player Interaction

The player interaction system allows objects to be interacted with by the player.  Objects that are interactable and in front of the player will be highlighted and can respond to begin and end interaction events when the player presses and releases inputs bound to the 'Interact' action mapping.

### Puzzle Nodes

Puzzle nodes allow level designers to cleanly and easily create interconnected dungeon puzzles like those found in Legend of Zelda or Skyrim.

Leaf nodes are meant to be set 'Solved' through interactions of the player. Parent nodes automatically evaluate to 'Solved' when all their children are solved.

For example two torches (nodes a and b) might need to be lit for a door (node c) to be unlocked.

The inheriting actor gets to decide what constitutes a puzzle node being 'solved'. They can have their own logic and state that ultimately results in it being solved or unsolved.

By chaining together puzzle node actors you can create elaborate puzzle dungeons that require multiple areas to be solved before the final node is solved.  You can set nodes up to allow the player to solve the dungeon puzzles in any order or in a specific order (by having nodes prevent access to other areas by using locked doors, draw bridges etc.)

Examples: 
* One or more simple torches, levers or switches that must be lit, pulled or pressed
* A series of statues that must be rotated to show certain images
* A combination lock that must be dialed to a certain number or series of glyphs
* A pedestal or area the player must move some other specified object onto
* Combinations:
  * A statue that must be rotated a certain way along with pulling a momentary lever to check if it's correct.


### Video

This video demonstrates the current functionality of the player interaction and puzzle node code.  Notice that lighting the three orbs is one sub-puzzle while lighting the firepits is another sub-puzzle.  When both sub-puzzles are 'solved' the fourth higher up orb automatically becomes lit.

[![Puzzle Node Video](http://img.youtube.com/vi/Sl4gk7NlG6Q/0.jpg)](http://www.youtube.com/watch?v=Sl4gk7NlG6Q)
<br/>https://www.youtube.com/watch?v=Sl4gk7NlG6Q

## Components vs Inheritance

There are two implementations of the player interaction system for comparison.

### Inheritance 

https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/AdventureGameCharacter.h
https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/Public/Interactable.h
https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/Public/InteractableActor.h

The files above implement a player interaction system using inheritance.  Designers can easily create derived blueprints that respond to the 'use' and 'stop using' blueprint events.  One flaw of this approach is it would be difficult to make classes that have already derived from actor (such as ACharacter) interactable.  This implementation can be demoed in the "ExampleMap".

### Components

https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/Public/Components/InteractionComponent.h
https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/Public/Components/InteractableComponent.h

The files above implement a player interaction system using components.  Designers can easily add an Interactable Component to any existing blueprint or class to make it player interactable.  This implementation can be demoed in the "TestMap".  For comparison, the NPC characters in this level have been given an interactable component that will make them jump when the player presses the interact key.  A drawback of this aproach could be the extra time required to determine if an actor contains an interactable component.

### Hybrid 

A hybrid aproach (not done here) could use both a component and inheritance (an interface) providing immediate knowledge of the behavior and access to the component.  You get the benefits of both but the draw back of requiring a little more setup work and  coding knowledge from the user.

## Other Code/UE4 Features

* UE4 Interfaces
* UE4 Typed Enums
* UE4 TArrays
* Soft Object References
* Basic 3D math
* AI
  * AI Controllers
  * Behavior Trees
  * Behavior Tree Tasks
  * Blackboards
* Events/Notifications by
  * virtual overrides
  * blueprint implementable events
  * blueprint native events
  * dynamic multicast delegates
* Use of Pointers and References
* Skeletal Animation Retargeting
* Materials (see HologramMap)
* Project Content Organization
 





