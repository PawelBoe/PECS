//
// Created by Pawel Boening on 01.09.18.
//

#include "core/EntityComponentSystem.h"
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
        for (auto entity : view)
        {
            view.get<ComponentA>(entity).A += 2 * dt;
        }
    }
};

class Application : public pecs::EntityComponentSystem
{
public:
    explicit  Application()
    {
        assign_system<SystemA>();
        assign_component<ComponentA>();

        for (int i = 0; i < 13; i++) {
            pecs::Entity entity = _data.create();
            _data.add<ComponentA>(entity);
            _data.get<ComponentA>(entity).A = 42;
        }
    }

    void simulate(float dt)
    {
        update<SystemA>(dt);
    }

    pecs::View<> & data()
    {
        return _data;
    }
};

TEST_CASE( "EntityComponentSystem full test", "[EntityComponentSystem]" )
{
    Application app;
    for (int i = 0; i < 10; i++) {
        app.simulate(0.5);
    }

    auto &view = app.data();
    int count = 0;
    for (auto entity : view)
    {
        count ++;
        REQUIRE( view.get<ComponentA>(entity).A == 52 );
    }
    REQUIRE( count == 13 );
}
