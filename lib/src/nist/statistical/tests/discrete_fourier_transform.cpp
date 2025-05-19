/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests/discrete_fourier_transform.hpp>

#include <algorithm>
#include <complex>
#include <vector>

#include <nist/statistical/tests/utilities.hpp>

namespace nist {
namespace statistical {
namespace tests {

   namespace {

      /**
       * Computes the Discrete Fourier Transform (DFT) of a real-valued input vector.
       *
       * @param X A vector of real-valued input samples.
       * 
       * @return The DFT output as a vector of complex numbers.
       */
      std::vector < std::complex < double > >
      dft ( const std::vector < double >& X )
      {
         const double PI = std::acos ( -1 );
         std::vector < std::complex < double > > S ( X.size () );

         for ( size_t j = 0; j < X.size (); j++ )
         {
            std::complex < double > sum ( 0.0, 0.0 );

            for ( size_t k = 1; k <= X.size (); k++ )
            {
               double angle = 2.0 * PI * ( k - 1 ) * j / X.size ();
               sum += X [ k - 1 ] * std::complex < double > ( std::cos ( angle ), std::sin ( angle ) );
            }

            S [ j ] = sum;
         }

         return S;
      }

   } // namespace

   //-----------------------------------------------------------------------------

   bool
   discrete_fourier_transform_test ( const uint8_t input [], size_t input_length )
   {
      // n >= 1000
      size_t total_bits = input_length * 8;
      if ( total_bits < 1000 ) return false;
      
      std::vector < double > X ( total_bits, 0x00 );
      for ( size_t i = 0; i < total_bits; i++ )
      {
         X [ i ] = ( 2.0 * utilities::get_bit ( input, i ) ) - 1.0;
      }
      
      auto S = dft ( X );
      
      size_t half_bits = total_bits / 2;
      std::vector < double > M ( half_bits, 0.0 );
      for ( size_t i = 0; i < M.size (); i++ )
      {
         M [ i ] = std::abs ( S [ i ] );
      }

      double T = std::sqrt ( std::log ( 1 / 0.05 ) * total_bits );

      double N0 = 0.95 * ( half_bits );

      size_t N1 = std::count_if ( M.begin (), M.end (),
         [ T ] ( double mag ) { return mag < T; } );

      double d = ( N1 - N0 ) / std::sqrt ( total_bits * 0.95 * 0.05 / 4.0 );

      double p_value = std::erfc ( std::abs ( d ) / std::sqrt ( 2.0 ) );
      return p_value >= 0.01;
   }

} // tests
} // statistical
} // nist