/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests/runs.hpp>

#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

#include <nist/statistical/tests/utilities.hpp>

namespace nist {
namespace statistical {
namespace tests {

   namespace {

      uint8_t
      get_bit ( const uint8_t input [], size_t bit_index )
      {
         size_t byte_index = bit_index / 8;
         size_t bit_offset = bit_index % 8;

         return ( input [ byte_index ] >> ( 7 - bit_offset ) ) & 0x01;
      }

   } // namespace

   //------------------------------------------------------------------------------

   bool
   runs_test ( const uint8_t input [], size_t input_length )
   {
      // n >= 100
      size_t total_bits = input_length * 8;
      if ( total_bits < 100 ) return false;

      int64_t ones = utilities::count_ones ( input, input_length );
      double pi = (double) ones / total_bits;
      double threshold = 2.0 / std::sqrt ( total_bits );

      // check runs precondition
      if ( std::abs ( pi - 0.5 ) >= threshold ) return false;

      size_t Vn = 1;
      for ( size_t idx = 1; idx < total_bits; idx++ )
      {
         if ( get_bit ( input, idx ) != get_bit ( input, idx - 1 ) ) Vn++;
      }

      double numerator = std::abs ( Vn - ( 2 * total_bits * pi * ( 1.0 - pi ) ) );
      double denominator = 2.0 * ( std::sqrt ( 2.0 * total_bits ) * pi * ( 1.0 - pi ) );
      double p_value = std::erfc ( numerator / denominator );

      return p_value >= 0.01;
   }

   //------------------------------------------------------------------------------

   bool
   longest_run_of_ones_test ( const uint8_t input [], size_t input_length )
   {
      throw std::runtime_error ( "Not implemented" );
   }

} // tests
} // statistical
} // nist