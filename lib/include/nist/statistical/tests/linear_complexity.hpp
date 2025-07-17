/***************************************************
 * Copyright (c) 2025 Paulino de la Fuente Lizcano
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#ifndef __NIST_STATISTICAL_TESTS_LINEAR_COMPLEXITY_HPP_
#define __NIST_STATISTICAL_TESTS_LINEAR_COMPLEXITY_HPP_

#include <cinttypes>
#include <cstddef>
#include <vector>

namespace nist {
namespace statistical {
namespace tests {
    
    /**
     * @brief Performs the NIST SP800-22r1a Linear Complexity Test (Test 2.10).
     *
     * The test determines whether the linear complexity of fixed-size blocks
     * within a binary sequence is consistent with what would be expected for
     * a truly random sequence. The test uses the Berlekamp–Massey algorithm
     * to estimate the linear complexity of each block.
     *
     * @param input         Pointer to the input bit sequence (binary values: 0 or 1).
     * @param input_length  Total number of bits in the input sequence.
     * @param block_length  Length of each block (M) to be analyzed. The number of blocks N = floor(input_length / block_length) must be ≥ 1.
     *
     * @return true if the sequence passes the test (p-value ≥ 0.01), false otherwise.
     */

    bool 
    linear_complexity_test ( const uint8_t input[], size_t input_length, size_t block_length );

} // tests
} // statistical
} // nist

#endif // __NIST_STATISTICAL_TESTS_LINEAR_COMPLEXITY_HPP_