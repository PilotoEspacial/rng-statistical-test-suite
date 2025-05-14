/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#ifndef __NIST_STATISTICAL_TESTS_UTILITIES_HPP_
#define __NIST_STATISTICAL_TESTS_UTILITIES_HPP_

#include <cinttypes>
#include <cstddef>

namespace nist {
namespace statistical {
namespace tests {
namespace utilities {

   /**
    * This function counts the number of bits set in a byte 
    * sequence.
    * 
    * @param input The byte sequence.
    * @param input_length The byte sequence length.
    * 
    * @return The number of bits set.
    */
   size_t
   count_ones ( const uint8_t input [], size_t input_length );

} // utilities
} // tests
} // statistical
} // nist

#endif // __NIST_STATISTICAL_TESTS_UTILITIES_HPP_