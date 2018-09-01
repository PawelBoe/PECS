//
// Created by Pawel Boening on 01.09.18.
//

#include "catch.hpp"

int Factorial( int number ) {
    return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
}

TEST_CASE( "Factorial Fail", "[Fail][Factorial]" ) {
    REQUIRE( Factorial(0) == 1 );
}

TEST_CASE( "Factorial Full Test", "[Full][Factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}