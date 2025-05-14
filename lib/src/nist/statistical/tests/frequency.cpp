/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests/frequency.hpp>

#include <cmath>

#include <nist/statistical/tests/utilities.hpp>

namespace nist {
namespace statistical {
namespace tests {

   bool
   frequency_test ( const uint8_t input [], size_t input_length )
   {
      size_t total_bits = input_length * 8;
      if ( total_bits < 100 ) return false;

      int64_t ones = utilities::count_ones ( input, input_length );
      int64_t zeros = total_bits - ones;

      size_t s_n = std::abs ( ones - zeros );
      double s_obs = s_n / std::sqrt ( (double) total_bits );
      double p_value = std::erfc ( s_obs / std::sqrt ( 2.0 ) );

      return p_value >= 0.01;
   }

} // tests
} // statistical
} // nist