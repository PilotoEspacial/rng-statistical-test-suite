/***************************************************
 * Copyright (c) 2025 Paulino de la Fuente
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

 #include <vector>

#include <catch2/catch_test_macros.hpp>
#include <nist/statistical/tests/linear_complexity.hpp>

TEST_CASE ( "Linear Complexity Test passes with valid input", "[linear_complexity]" ) 
{
    const std::vector<uint8_t> test_vector = 
    {
        0b11001001, 0b00001111, 0b11011010, 0b10100010, 
        0b00100001, 0b01101000, 0b11000010, 0b00110100, 
        0b11000100, 0b11000110, 0b01100010, 0b10001011,
        0b10000000
    };

    using namespace nist::statistical::tests; 
    REQUIRE ( linear_complexity_test ( test_vector.data (), test_vector.size (), 64 ) == true );
}

TEST_CASE ( "Linear Complexity Test fails with patterned input", "[linear_complexity]" ) 
{
    std::vector < uint8_t > test_vector ( 128 );
    
    for ( size_t i = 0; i < test_vector.size (); ++i ) 
    {
        test_vector [ i ] = i % 2 ? 0xFF : 0x00;  // Alternating bytes full of 1s and 0s
    }

    using namespace nist::statistical::tests;
    REQUIRE ( linear_complexity_test ( test_vector.data (), test_vector.size (), 64 ) == false );
}

