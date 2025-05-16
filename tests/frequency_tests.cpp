/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist/statistical/tests/frequency.hpp>

namespace {

   const std::vector < uint8_t > valid_test_vector =
   {
      0b11001001, 0b00001111, 0b11011010, 0b10100010, 
      0b00100001, 0b01101000, 0b11000010, 0b00110100, 
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b1000
   };

   const std::vector < uint8_t > invalid_test_vector =
   {
      0b00000000, 0b00000000, 0b00000000, 0b00000000,
      0b00000000, 0b00000000, 0b00000000, 0b11111111,
      0b11000100, 0b11000110, 0b01100010, 0b10001011,
      0b1000
   };;

} // namespace

//--------------------------------------------------------------------------------

TEST_CASE("Frequency (Monobit) Test pass with valid input", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test ( valid_test_vector.data (), valid_test_vector.size () ) == true);
}

TEST_CASE("Frequency (Monobit) Test fails with invalid input", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test ( invalid_test_vector.data (), invalid_test_vector.size () ) == false);
}

//--------------------------------------------------------------------------------

TEST_CASE("Frequency Test within a Block pass with valid input", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test_within_a_block ( valid_test_vector.data (), valid_test_vector.size (), 20 ) == true);
}

TEST_CASE("Frequency Test within a Block fails with invalid input", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test_within_a_block ( invalid_test_vector.data (), invalid_test_vector.size (), 20 ) == false);
}

TEST_CASE("Frequency Test within a Block fails with invalid block size", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test_within_a_block ( valid_test_vector.data (), valid_test_vector.size (), 10 ) == false);
}