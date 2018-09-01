//
// Created by Pawel Boening on 01.09.18.
//

#include "catch.hpp"

#include "../src/util/sparse_set.h"
#include "../src/util/sparse_map.h"
#include "../src/Entity.h"


TEST_CASE( "sparse_set creation and deletion of 10000 entities", "[sparse_set]")
{
    pecs::sparse_set<pecs::Entity, pecs::Entity::Hash> sset;

    for (int i = 0; i < 10000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        sset.add(e);
    }

    REQUIRE( sset.size() == 10000 );

    for (int i = 0; i < 10000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        REQUIRE( sset.search(e) < sset.size() );
        sset.remove(e);
        REQUIRE( sset.search(e) >= sset.size() );
    }
}

TEST_CASE( "sparse_set mixed creation and deletion of 10000 entities", "[sparse_set]")
{
    pecs::sparse_set<pecs::Entity, pecs::Entity::Hash> sset;

    for (int i = 0; i < 3000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        sset.add(e);
    }

    REQUIRE( sset.size() == 3000 );

    for (int i = 0; i < 3000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        REQUIRE( sset.search(e) < sset.size() );
        sset.remove(e);
        REQUIRE( sset.search(e) >= sset.size() );
    }

    for (int i = 0; i < 7000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        sset.add(e);
    }

    REQUIRE( sset.size() == 7000 );

    for (int i = 0; i < 7000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        REQUIRE( sset.search(e) < sset.size() );
        sset.remove(e);
        REQUIRE( sset.search(e) >= sset.size() );
    }
}

TEST_CASE( "sparse_map creation and deletion of 10000 entities", "[sparse_map]")
{
    pecs::sparse_map<pecs::Entity, int, pecs::Entity::Hash> smap;

    for (int i = 0; i < 10000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        smap.add(e, i);
    }

    REQUIRE( smap.size() == 10000 );

    for (int i = 0; i < 10000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        REQUIRE( smap.search(e) < smap.size() );
        smap.remove(e);
        REQUIRE( smap.search(e) >= smap.size() );
    }
}

TEST_CASE( "sparse_map mixed creation and deletion of 10000 entities", "[sparse_map]")
{
    pecs::sparse_map<pecs::Entity, int, pecs::Entity::Hash> smap;

    for (int i = 0; i < 3000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        smap.add(e, i);
    }

    REQUIRE( smap.size() == 3000 );

    for (int i = 0; i < 3000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        REQUIRE( smap.search(e) < smap.size() );
        smap.remove(e);
        REQUIRE( smap.search(e) >= smap.size() );
    }

    for (int i = 0; i < 7000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        smap.add(e, i);
    }

    REQUIRE( smap.size() == 7000 );

    for (int i = 0; i < 7000; ++i) {
        pecs::Entity e(static_cast<pecs::EntityIndex>(i), 0);
        REQUIRE( smap.search(e) < smap.size() );
        smap.remove(e);
        REQUIRE( smap.search(e) >= smap.size() );
    }
}
