# PECS - Pawel's Entity Component System
This project implements a basic ECS in C++11 based on custom
[sparse sets](https://programmingpraxis.com/2012/03/09/sparse-sets/),
[this article](http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/)
 and some C++ template magic. It prioritizes ease of
 use and support of rather basic ECS features, so there is for
 example no event handling at the moment. It was
build from scratch mainly as a learning experience to make a type-save
component and system management. But now it also serves as
the basis for some games that I am loosely working on right now.

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

## Tutorial
To get started put the `/src` directory in your include path and add
this to your source files:
``` c++
#include "pecs.h"
```

### Entities
All entities that are used anywhere should first be created using the
`pecs::EntityManager`:
``` c++
pecs::EntityManager entity_manager;
pecs::Entity entity = entity_manager.create();
```

To access all created entities, you can iterate over the entity manager
in a for loop like this:
``` c++
for (pecs::Entity e : entity_manager) {
    // do something with e
}
```

You can also query for a specific entity`s existence within
the EntityManager or remove it:
``` c++
entity_manager.exists(entity); // true

entity_manager.remove(entity);

entity_manager.exists(entity); // false
```

Creating an entity on your own works like this:
``` c++
pecs::Entity entity(42, 13);

// entity.index() == 42
// entity.version() == 13
```

Internally an entity only has a single 32 bit number which contains two
parts: 24 bit for index and 8 bit for version. The index is the entity's
identity, the "thing" that it actually "is". The version serves as a
way to invalidate an entity once it is removed. This way any dangling
references remaining somewhere in systems or components are different
from a newly created entity with the same index for example (since entity
indices are reusable). Also this actually allows to keep invalid entities
around until they are ready to be removed by the user, without having to
fear dereferencing an invalid pointer.


### Components
As mentioned in my guiding principles above, components should be POD
(plain old data). This means that no behavior or logic is attached to
them and that behavior is implemented in systems which communicate via
the state of the components' data.

Here is a basic example of the definition of some common components:
``` c++
struct Position
{
    int x;
    int y
};

struct Velocity
{
    int dx;
    int dx
};
```

To be able to use a component and to be able to give it to an entity, it
first must be assigned to a `pecs::ComponentManager`:
``` c++
pecs::ComponentManager component_manager;

// assign Position and Velocity to the manager
component_manager.assign<Position>();
component_manager.assign<Velocity>();

// create a Position and a Velocity component for the entity
component_manager.add<Position>(entity);
component_manager.add<Velocity>(entity);
```

Now getting the data of the component or changing it is easy:
``` c++
component_manager.get<Position>(entity).x = 1;
component_manager.get<Position>(entity).y = 1;

component_manager.get<Velocity>(entity).dx = 1;
component_manager.get<Velocity>(entity).dy = 1;
```

Testing for a components existence and also its removal work analogously:
``` c++
component_manager.exists<Position>(entity); // true
component_manager.remove<Position>(entity);
component_manager.exists<Position>(entity); // false
```


### Views
Views are a mechanism to abstract away the use of the different managers
mentioned earlier. They provide a limited access to components and
entities, based on a `pecs::Signature<Components..>`. As entities get
created and changed, the different views get notified of that and if the
corresponding entity now matches the signature, it gets added to the
view's cache.

Views can be looped over and they provide a complete interface to
component and entity managers:

``` c++
    pecs::ViewManager view_manager(entity_manager, component_manager);

    pecs::Signature<Position, Velocity> signature;

    pecs::View<Position, Velocity> &view = view_manager.get<signature>();

    for (pecs::Entity e : view) {
        view.get<Position>(e) = 42; // change value of component
        view.remove<Velocity>(e); // remove component

        // ..

        pecs::Entity e = view.create(); // create new entity
        view.add<Position>(); // add component
        view.remove(e); // remove entity

        // ..
    }
```


### Systems
To implement logic and behavior, systems are used. They process entities,
based on a signature declaration that is provided as a series of template
parameters to their superclass like so:

``` c++
// pecs::Signature<Position, Velocity> is the internal signature here..
class MovementSystem : public pecs::System<MovementSystem, Position, Velocity>
{
    void update(pecs::View<Position, Velocity> &view, float dt)
    {
        for (pecs::Entity e : view) {
            view.get<Position>(e).x = view.get<Velocity>(e).x * dt;
            view.get<Position>(e).y = view.get<Velocity>(e).y * dt;
        }
    }
};
```

Each system needs to provide an `update()` method that receives a `pecs::View<Components...>`
according to its signature, as seen above. Also a variable number of
arguments can follow, like in this example `float dt`.


### EntityComponentSystem
Finally there exists `ecs::EntityComponentSystem` which serves as a wrapper
to all previously discussed concepts. It allows to tie together all systems,
components and to initialize some entities within the ECS. Notice that
the helper methods `assign_system<System>()` and `assign_component<Component>()`
are used to register the user-provided parts to the ECS. Furthermore there
is a protected member `_data` which represents a `pecs::View<>` that allows
for unconstrained access to all entities in the ECS.
```c++
class Application : public pecs::EntityComponentSystem
{
public:
    Application()
    {
        // assign user defined systems to internal system manager
        assign_system<MovementSystem>();

        // assign user defined components to internal component manager
        assign_component<Position>();
        assign_component<Velocity>();

        // initialize some world data
        pecs::Entity e = _data.create();
        _data.add<Position>(e);
        _data.get<Position>(e).x = 42;
        _data.get<Position>(e).y = 42;
        _data.add<Velocity>(e);
        _data.get<Velocity>(e).x = 42;
        _data.get<Velocity>(e).y = 42;
    }

    void simulate(float dt)
    {
        // perform a single iteration over systems
        update<MovementSystem>(dt);
    }
};
```

## Installation
I have not thought about a build system yet so..
Just clone the current version and copy the contents of `/src` wherever
you want them to be, include `pecs.h` and you are good to go!

## Tests and Examples
TODO How to compile examples

TODO what do they show

