//
// Created by Pawel Boening on 01.09.18.
//

#include "catch.hpp"

#include "../src/View.h"


TEST_CASE( "View external entity creation and matching", "[View]" )
{
    struct Component_0 { };
    struct Component_1 { int x; };

    pecs::ComponentManager components;
    components.add<Component_0>();
    components.add<Component_1>();

    pecs::EntityManager entities;
    for (int i = 0; i < 10; i++) {
        auto e = entities.create();
        components.create<Component_0>(e);
    }
    for (int i = 0; i < 20; i++) {
        auto e = entities.create();
        components.create<Component_0>(e);
        components.create<Component_1>(e);
    }

    pecs::Signature<Component_0> signature_0;
    pecs::Signature<Component_0, Component_1> signature_1;

    pecs::ViewFactory view_factory(entities, components);
    view_factory.create(signature_0);
    view_factory.create(signature_1);

    int count = 0;
    for (auto e : view_factory.view(signature_0)) {
        count ++;
        REQUIRE( signature_0.match(components, e) );
    }
    REQUIRE( count == 30 );

    count = 0;
    for (auto e : view_factory.view(signature_1)) {
        count ++;
        REQUIRE( signature_0.match(components, e) );
        REQUIRE( signature_1.match(components, e) );
    }
    REQUIRE( count == 20 );

}

TEST_CASE( "View internal entity creation", "[View]" )
{
    struct Component_0 { int x; };
    struct Component_1 { int x; };

    pecs::ComponentManager components;
    components.add<Component_0>();
    components.add<Component_1>();

    pecs::EntityManager entities;

    pecs::Signature<Component_0> signature_0;
    pecs::Signature<Component_0, Component_1> signature_1;

    pecs::ViewFactory view_factory(entities, components);
    view_factory.create(signature_0);
    view_factory.create(signature_1);

    pecs::Entity entity_0 = view_factory.view(signature_0).create();
    view_factory.view(signature_0).create<Component_0>(entity_0);
    view_factory.view(signature_0).create<Component_1>(entity_0);
    view_factory.view(signature_0).component<Component_0>(entity_0).x = 42;
    view_factory.view(signature_0).component<Component_1>(entity_0).x = 13;

    int count = 0;
    for (auto e : view_factory.view(signature_0)) {
        count ++;
        REQUIRE( view_factory.view(signature_0).component<Component_0>(e).x == 42 );
    }
    REQUIRE( count == 1);

    count = 0;
    for (auto e : view_factory.view(signature_1)) {
        count ++;
        REQUIRE( view_factory.view(signature_1).component<Component_0>(e).x == 42 );
        REQUIRE( view_factory.view(signature_1).component<Component_1>(e).x == 13 );
    }
    REQUIRE( count == 1);
}
