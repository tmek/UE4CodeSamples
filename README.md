# UE4CodeSamples

Hi! This project is meant to demonstrate project organization and coding proficiency when working with Unreal Engine 4.

The sample code adheres to a coding standard.  In this case

https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard

## Overview

This project showcases two features.  A player interaction system and a puzzle node system.

### Player Interaction

### Puzzle Nodes

### Video

This video demonstrates the current functionality of the player interaction and puzzle node code.

[![Puzzle Node Video](http://img.youtube.com/vi/Sl4gk7NlG6Q/0.jpg)](http://www.youtube.com/watch?v=Sl4gk7NlG6Q)

https://www.youtube.com/watch?v=Sl4gk7NlG6Q

## Composition vs Inheritence

There are two implementations of the player interaction system for comparison.

### Inheritance 

The files:

https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/AdventureGameCharacter.h
https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/Public/Interactable.h
https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/Public/InteractableActor.h

Implement a player interaction system using inheritance.  Designers can easily create derived blueprints that responde to the use and stop using blueprint events.  One flaw of this approach is it would be difficult to make classes that have already derived from actor (such as ACharacter) interactable.

### Composition

The files:

https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/Public/Components/InteractionComponent.h
https://github.com/tmek/UE4CodeSamples/blob/master/Source/AdventureGame/Public/Components/InteractableComponent.h

Implements a player interaction system using composition.  Designers can easily  add an Interactable Component to any existing blueprint or class to make it player interactable.







