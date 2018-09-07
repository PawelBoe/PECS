//
// Created by Pawel Boening on 01.09.18.
//

#include "catch.hpp"

#include "core/Entity.h"
#include "core/EntityManager.h"


TEST_CASE( "Entity creation and deletion", "[Entity]" )
{
    pecs::Entity entity(42, 13);

    REQUIRE( entity.index() == 42 );
    REQUIRE( entity.version() == 13);
}

TEST_CASE( "Entity comparison", "[Entity]" )
{
    pecs::Entity entity_0(42, 13);
    pecs::Entity entity_1(42, 13);
    pecs::Entity entity_2(42, 42);
    pecs::Entity entity_3(13, 13);
    pecs::Entity entity_4(13, 42);

    REQUIRE( entity_0 == entity_0 );
    REQUIRE( entity_0 == entity_1 );
    REQUIRE( entity_0 != entity_2 );
    REQUIRE( entity_0 != entity_3 );
    REQUIRE( entity_0 != entity_4 );
}

TEST_CASE( "EntityManager creation and deletion of 1M entities", "[EntityManager]" )
{
    pecs::EntityManager entity_manager;
    int amount = 1000000;

    for (int i = 0; i < amount; ++i) {
        entity_manager.create();
    }

    int count = 0;
    for (auto e : entity_manager) {
        count++;
        REQUIRE( entity_manager.exists(e) );
        entity_manager.remove(e);
        REQUIRE( !entity_manager.exists(e) );
    }

    REQUIRE( count == amount );
}

TEST_CASE( "EntityManager mixed creation and deletion of 10k entities", "[EntityManager]")
{
    pecs::EntityManager entity_manager;
    std::vector<int> entity_amounts = {3000, 7000, 100, 666, 1000, 10000};

    for (int amount : entity_amounts) {
        for (int i = 0; i < amount; ++i) {
            entity_manager.create();
        }

        int count = 0;
        for (auto e : entity_manager) {
            count++;
            REQUIRE( entity_manager.exists(e) );
            entity_manager.remove(e);
            REQUIRE( !entity_manager.exists(e) );
        }

        REQUIRE( count == amount );
    }
}