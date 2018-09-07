# PECS - Pawel's Entity Component System
An entity component system (ECS) is a design pattern that makes
use of composition rather than inheritance to achieve code reuse and
polymorphic behavior. Entities consist of multiple components. These
components can be seen as the attributes that define the data an entity
has. Systems operate on these entities, being able to modify, create
and remove components and entities.
In a sense components define the data whereas the systems define the
behavior of associated entities.

This project implements a basic ECS in C++11 based on custom
[sparse sets](https://programmingpraxis.com/2012/03/09/sparse-sets/),
[this article](http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/)
 and some C++ template magic. It prioritizes ease of
 use and support of rather basic ECS features, so there is for
 example no event handling at the moment. It was
build from scratch mainly as a learning experience to make a type-save
component and system management. But now it also serves as
the basis for a game that I am loosely working on right now.

## Tutorial
PECS takes a very simplistic approach to ECS:
- Entities are just identity
- Components are just data
- Systems are just behavior

An entity simply represents an ID to distinguish itself from other entities.
This ID/entity can be associated with data stored in components. So  an
entity matches a certain signature, that is characterized by the set of
components currently attached to it. A system on the other hand implements
the logic that acts on an entity's components. To announce what entities a
system wants to operate on, it also has a signature. Thus by matching the
right entity to the right system, entities with certain components get
certain behavior.

- Interaction between entities does not happen, because they do not act
- Interaction between components does not happen, because they do not act
- Interaction between systems does only happen through entity data

You can of course take a different approach to this, just know that PECS
was designed primarily with these points in mind.

### Entities
TODO

### Components
TODO

### Systems
TODO

### EntityComponentSystem
TODO

## Installation
I have not thought about a build system yet so..
Just clone the current version and copy the contents of `/src` wherever
you want them to be, include `pecs.h` and you are good to go!

## Tests and Examples
TODO How to compile examples
TODO what do they show

