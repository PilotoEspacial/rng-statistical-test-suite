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
   REQUIRE ( runs_test ( valid_test_vector.data (), valid_test_vector.size () ) == true);
}

TEST_CASE("Runs Test fails with invalid input", "[runs]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( runs_test ( invalid_test_vector.data (), invalid_test_vector.size () ) == false);
}