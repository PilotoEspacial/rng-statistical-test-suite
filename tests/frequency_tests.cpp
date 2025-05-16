/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist/statistical/tests/frequency.hpp>

#include "test_vectors.hpp"

TEST_CASE("Frequency (Monobit) Test pass with valid input", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test ( TEST_VECTOR_1.data (), TEST_VECTOR_1.size () ) == true);
}

TEST_CASE("Frequency (Monobit) Test fails with invalid input", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test ( TEST_VECTOR_2.data (), TEST_VECTOR_2.size () ) == false);
}

//--------------------------------------------------------------------------------

TEST_CASE("Frequency Test within a Block pass with valid input", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test_within_a_block ( TEST_VECTOR_1.data (), TEST_VECTOR_1.size (), 20 ) == true);
}

TEST_CASE("Frequency Test within a Block fails with invalid input", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test_within_a_block ( TEST_VECTOR_2.data (), TEST_VECTOR_2.size (), 20 ) == false);
}

TEST_CASE("Frequency Test within a Block fails with invalid block size", "[frequency]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( frequency_test_within_a_block ( TEST_VECTOR_1.data (), TEST_VECTOR_1.size (), 10 ) == false);
}