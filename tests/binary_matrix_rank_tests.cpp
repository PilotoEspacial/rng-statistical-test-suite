/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <catch2/catch_test_macros.hpp>
#include <nist/statistical/tests/binary_matrix_rank.hpp>

#include "test_vectors.hpp"

TEST_CASE("Binary Matrix Rank Test fails with invalid input", "[binary-matrix-rank]")
{
   using namespace nist::statistical::tests;
   REQUIRE ( binary_matrix_rank_test ( TEST_VECTOR_1.data (), TEST_VECTOR_1.size () ) == false);
}