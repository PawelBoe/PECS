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
[sparse sets](https://programmingpraxis.com/2012/03/09/sparse-sets/).
Its prioritizes the ease of use and the support of more basic ECS
features, so there is for example no event system at the moment. It was
build from scratch mainly as a learning experience to make a type-save
component and system management. But now it also serves as
the basis for a game that I am loosely working on right now.

## Tutorial
TODO

### Entities

### Components

### Systems

### EntityComponentSystem

## Installation
I have not thought about a build system yet so..
Just clone the current version and copy the contents of `/src` wherever
you want them to be, include `pecs.h` and you are good to go!

## Tests and Examples
TODO How to compile examples
TODO what do they show

