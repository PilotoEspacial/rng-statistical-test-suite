/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist/statistical/tests/runs.hpp>

#include "test_vectors.hpp"

TEST_CASE("Runs Test pass with valid input", "[runs]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( runs_test ( TEST_VECTOR_1.data (), TEST_VECTOR_1.size () ) == true);
}

TEST_CASE("Runs Test fails with invalid input", "[runs]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( runs_test ( TEST_VECTOR_2.data (), TEST_VECTOR_2.size () ) == false);
}

//--------------------------------------------------------------------------------

TEST_CASE("Longest Run of Ones in a Block Test pass with valid input", "[runs]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( runs_test ( TEST_VECTOR_4.data (), TEST_VECTOR_4.size () ) == true);
}

TEST_CASE("Longest Run of Ones in a Block Test fails with invalid input", "[runs]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( runs_test ( TEST_VECTOR_5.data (), TEST_VECTOR_5.size () ) == false);
}