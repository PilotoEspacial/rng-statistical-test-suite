/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests/discrete_fourier_transform.hpp>

#include <algorithm>
#include <complex>
#include <vector>

#include <iostream>

namespace nist {
namespace statistical {
namespace tests {

   namespace
   {

      std::vector < std::complex < double > >
      dft ( const std::vector < int8_t >& input )
      {
         throw std::runtime_error ( "Not implemented" );
      }

   } // namespace

   bool
   discrete_fourier_transform_test ( const uint8_t input [], size_t input_length )
   {
      // n >= 1000
      size_t total_bits = input_length * 8;
      if ( total_bits < 1000 ) return false;

      std::vector < int8_t > X ( total_bits, 0x00 );
      for ( size_t i = 0; i < total_bits; i++ )
      {
         size_t byte_index = i / 8;
         size_t bit_index  = 7 - ( i % 8 );
         uint8_t bit = ( input [ byte_index ] >> bit_index ) & 0x01;
         X [ i ] = 2 * bit - 1;
      }

      auto S = dft ( X );
      
      std::vector < double > M ( total_bits / 2.0, 0.0 );
      for ( size_t k = 0; k < M.size (); k++ )
      {
         M [ k ] = std::abs ( S [ k ] );
      }

      double T = std::sqrt ( std::log ( 1 / 0.05 ) * total_bits );

      double N0 = 0.95 * ( total_bits / 2.0 );

      size_t N1 = std::count_if ( M.begin (), M.end (),
         [ T ] ( double mag ) { return mag < T; } );

      double d = ( N1 - N0 ) / std::sqrt ( total_bits * 0.95 * 0.05 / 4.0 );

      double p_value = std::erfc ( std::abs ( d ) / std::sqrt ( 2.0 ) );
      return p_value >= 0.01;
   }

} // tests
} // statistical
} // nist