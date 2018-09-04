//
// Created by Pawel Boening on 01.09.18.
//

#include "catch.hpp"

#include "../src/Signature.h"


TEST_CASE( "Signature creation and matching", "[Signature]" )
{
    struct Component_0 { };
    struct Component_1 { int x; };
    struct Component_2 { int x; int y; };

    pecs::Entity entity_0(0, 0);
    pecs::Entity entity_1(1, 0);

    pecs::ComponentManager components;
    components.add<Component_0>();
    components.add<Component_1>();
    components.add<Component_2>();

    components.create<Component_0>(entity_0);
    components.create<Component_1>(entity_0);
    components.create<Component_0>(entity_1);
    components.create<Component_2>(entity_1);

    pecs::Signature<Component_0> signature_0;
    pecs::Signature<Component_0, Component_1> signature_1;
    pecs::Signature<Component_0, Component_1, Component_2> signature_2;
    pecs::Signature<Component_0, Component_2> signature_3;

    REQUIRE( signature_0.match(components, entity_0) );
    REQUIRE( signature_1.match(components, entity_0) );
    REQUIRE( !signature_2.match(components, entity_0) );
    REQUIRE( !signature_3.match(components, entity_0) );

    REQUIRE( signature_0.match(components, entity_1) );
    REQUIRE( !signature_1.match(components, entity_1) );
    REQUIRE( !signature_2.match(components, entity_1) );
    REQUIRE( signature_3.match(components, entity_1) );

    components.create<Component_2>(entity_0);
    components.create<Component_1>(entity_1);

    REQUIRE( signature_2.match(components, entity_0) );
    REQUIRE( signature_3.match(components, entity_0) );

    REQUIRE( signature_1.match(components, entity_1) );
    REQUIRE( signature_2.match(components, entity_1) );

    components.remove<Component_0>(entity_0);
    components.remove<Component_0>(entity_1);

    REQUIRE( !signature_0.match(components, entity_0) );
    REQUIRE( !signature_1.match(components, entity_0) );
    REQUIRE( !signature_2.match(components, entity_0) );
    REQUIRE( !signature_3.match(components, entity_0) );

    REQUIRE( !signature_0.match(components, entity_1) );
    REQUIRE( !signature_1.match(components, entity_1) );
    REQUIRE( !signature_2.match(components, entity_1) );
    REQUIRE( !signature_3.match(components, entity_1) );
}

TEST_CASE( "SignatureBase creation and matching", "[Signature][SignatureBase]" )
{
    struct Component_0 { };
    struct Component_1 { int x; };
    struct Component_2 { int x; int y; };

    pecs::Entity entity_0(0, 0);
    pecs::Entity entity_1(1, 0);

    pecs::ComponentManager components;
    components.add<Component_0>();
    components.add<Component_1>();
    components.add<Component_2>();

    components.create<Component_0>(entity_0);
    components.create<Component_1>(entity_0);
    components.create<Component_2>(entity_0);

    std::vector<pecs::SignatureBase*> signatures;

    signatures.push_back(new pecs::Signature<Component_0>);
    signatures.push_back(new pecs::Signature<Component_1>);
    signatures.push_back(new pecs::Signature<Component_2>);
    signatures.push_back(new pecs::Signature<Component_0, Component_1>);
    signatures.push_back(new pecs::Signature<Component_0, Component_2>);
    signatures.push_back(new pecs::Signature<Component_1, Component_2>);
    signatures.push_back(new pecs::Signature<Component_0, Component_1, Component_2>);

    for (auto signature : signatures) {
        REQUIRE( signature->match(components, entity_0) );
        REQUIRE( !signature->match(components, entity_1) );
    }

    components.remove<Component_0>(entity_0);
    components.remove<Component_1>(entity_0);
    components.remove<Component_2>(entity_0);
    components.create<Component_0>(entity_1);
    components.create<Component_1>(entity_1);
    components.create<Component_2>(entity_1);

    for (auto signature : signatures) {
        REQUIRE( !signature->match(components, entity_0) );
        REQUIRE( signature->match(components, entity_1) );
    }

    for (auto signature : signatures) {
        delete signature;
    }
    signatures.clear();
}

TEST_CASE( "Empty signature creation ", "[Signature]" )
{
    struct Component_0 { };

    pecs::Entity entity_0(0, 0);

    pecs::ComponentManager components;
    components.add<Component_0>();
    components.create<Component_0>(entity_0);

    pecs::Signature<> signature_0;

    REQUIRE( signature_0.match(components, entity_0) );
}
