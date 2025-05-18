/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist/statistical/tests/discrete_fourier_transform.hpp>

TEST_CASE("Discrete Fourier Transform (Spectral) Test pass with valid input", "[spectral]")
{
   const std::vector < uint8_t > test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b10000000
   };

   using namespace nist::statistical::tests;
   REQUIRE ( discrete_fourier_transform_test ( test_vector.data (), test_vector.size () ) == true);
}