//
// Created by Pawel Boening on 01.09.18.
//

#include "catch.hpp"

#include "../src/util/sparse_set.h"
#include "../src/util/sparse_map.h"
#include "core/Entity.h"

TEST_CASE( "sparse_set creation and deletion of 1M entities", "[sparse_set]")
{
    pecs::sparse_set<pecs::Entity, pecs::Entity::Hash> sset;
    int amount = 1000000;

    for (int i = 0; i < amount; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        sset.add(e);
    }

    REQUIRE( sset.size() == amount );

    for (int i = 0; i < amount; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        REQUIRE( sset.search(e) < sset.size() );
        sset.remove(e);
        REQUIRE( sset.search(e) >= sset.size() );
    }
}

TEST_CASE( "sparse_set mixed creation and deletion of 10k entities", "[sparse_set]")
{
    pecs::sparse_set<pecs::Entity, pecs::Entity::Hash> sset;

    std::vector<int> entity_amounts = {3000, 7000, 100, 666, 1000, 10000};

    for (int amount : entity_amounts) {
        for (int i = 0; i < amount; ++i) {
            pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
            sset.add(e);
        }

        REQUIRE( sset.size() == amount );

        for (int i = 0; i < amount; ++i) {
            pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
            REQUIRE( sset.search(e) < sset.size() );
            sset.remove(e);
            REQUIRE( sset.search(e) >= sset.size() );
        }
    }
}

TEST_CASE( "sparse_map creation and deletion of 1M entities", "[sparse_map]")
{
    pecs::sparse_map<pecs::Entity, int, pecs::Entity::Hash> smap;
    int amount = 1000000;

    for (int i = 0; i < amount; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        smap.add(e, i);
    }

    REQUIRE( smap.size() == amount );

    for (int i = 0; i < amount; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        REQUIRE( smap.search(e) < smap.size() );
        smap.remove(e);
        REQUIRE( smap.search(e) >= smap.size() );
    }
}

TEST_CASE( "sparse_map mixed creation and deletion of 10k entities", "[sparse_map]")
{
    pecs::sparse_map<pecs::Entity, int, pecs::Entity::Hash> smap;

    std::vector<int> entity_amounts = {3000, 7000, 100, 666, 1000, 10000};

    for (int amount : entity_amounts) {
        for (int i = 0; i < amount; ++i) {
            pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
            smap.add(e, i);
        }

        REQUIRE( smap.size() == amount );

        for (int i = 0; i < amount; ++i) {
            pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
            REQUIRE( smap.search(e) < smap.size() );
            smap.remove(e);
            REQUIRE( smap.search(e) >= smap.size() );
        }
    }
}
