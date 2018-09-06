//
// Created by Pawel Boening on 01.09.18.
//

#include "EntityComponentSystem.h"
#include "catch.hpp"

struct ComponentA
{
    int A;
};

class SystemA : public pecs::System<SystemA, ComponentA>
{
public:
    void _update(pecs::View<ComponentA> &view, float dt)
    {

    }
};

class Application : public pecs::EntityComponentSystem
{
public:
    explicit  Application()
    {
        add_system<SystemA>();
        add_component<ComponentA>();
    }

    void simulate(float dt)
    {
        update<SystemA>(dt);
    }
};

TEST_CASE( "EntityComponentSystem full test", "[EntityComponentSystem]" )
{
    Application app;
    app.simulate(1);
}
